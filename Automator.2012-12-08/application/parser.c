/* Name: parser.c
 * Project: Automator
 * Author: Christian Starkjohann
 * Creation Date: 2006-02-11
 * Tabsize: 4
 * Copyright: (c) 2006 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: Proprietary, free under certain conditions. See Documentation.
 * This Revision: $Id$
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "parser.h"

int  parserLineNr;

/* ------------------------------------------------------------------------- */

void    parserWriteProgram(FILE *fp, char data[512])
{
int             i, length = ((unsigned)(unsigned char)data[1] << 8) | (unsigned)(unsigned char)data[0];
unsigned        duration;
unsigned char   action, bit;
char            timeBuf[64];
time_t          now;
struct tm       *tm;

    fprintf(fp, "# Automator program file\n");
    now = time(NULL);
    tm = localtime(&now);
    strftime(timeBuf, 64, "%Y-%m-%d %H:%M:%S", tm);
    fprintf(fp, "# Downloaded from device at %s\n", timeBuf);
    fprintf(fp, "# Commands are:\n");
    fprintf(fp, "# set <bit> ...................... set output port nr. <bit>\n");
    fprintf(fp, "# clear <bit> .................... clear output port nr. <bit>\n");
    fprintf(fp, "# set_pulse <bit> <duration> ..... set port <bit> for <duration> cycles\n");
    fprintf(fp, "# clear_pulse <bit> <duration> ... clear port <bit> for <duration> cycles\n");
    fprintf(fp, "# wait_input <bit> ............... wait for input on input port <bit>\n");
    fprintf(fp, "# delay <duration> ............... do nothing for <duration> cycles\n");
    fprintf(fp, "\n");
    if(length > 510)
        length = 510;
    for(i=0;i<length;i++){
        action = data[i + 2];
        switch(action & 0xc0){
        case 0:     /* set bit: 0 0 T T T B B B */
        case 0x40:  /* clear bit: 0 1 T T T B B B */
            bit = action & 7;
            duration = (action >> 3) & 7;
            fprintf(fp, (action & 0x40) ? "clear" : "set");
            if(duration == 0){
                fprintf(fp, " %d\n", bit);
            }else{
                fprintf(fp, "_pulse %d %d\n", bit, duration);
            }
            break;
        case 0x80:  /* wait for evnt: 1 0 0 0 0 0 B B */
            fprintf(fp, "wait_input %d\n", action & 3);
            break;
        case 0xc0:  /* delay: 1 1 U U T T T T */
            duration = 0;
            switch(action & 0x30){
            case 0:
            case 0x10:
                duration = (action & 0x1f) + 1;
                break;
            case 0x20:
                duration = (unsigned)(action & 0xf) << 5;
                break;
            case 0x30:
                duration = (unsigned)(action & 0xf) << 9;
                break;
            }
            fprintf(fp, "delay %d\n", duration);
            break;
        }
    }
}

/* ------------------------------------------------------------------------- */

static char *parseToken(char **pp)
{
char    *token, *endToken, *s = *pp;

    while(*s && isspace(*s))
        s++;
    if(*s == 0)
        return NULL;
    token = s;
    while(*s && (!isspace(*s) && *s != ',' && *s != ';'))
        s++;
    endToken = s;
    while(*s && (isspace(*s) || *s == ',' || *s == ';'))
        s++;
    *pp = s;    /* points to start of next token now */
    *endToken = 0;
    return token;
}

static int  parseNumber(char **pp, int *number)
{
char    *p = *pp;
char    *num = parseToken(&p);

    if(num == NULL)
        return 0;
    if(!isdigit(*num))
        return 0;
    *pp = p;
    *number = atoi(num);
    return 1;
}

#define WRITE_ACTION(x) if(i >= 512) return PARSE_ERROR_CODE_OVERFLOW; data[i++] = (x)

int parserReadProgram(FILE *fp, char data[512])
{
int     i = 2;
char    *p, *cmd, line[256];

    for(parserLineNr=1;;parserLineNr++){
        if(fgets(line, sizeof(line), fp) == NULL)   /* EOF or error */
            break;
        p = line;
        if((cmd = parseToken(&p)) == NULL || cmd[0] == '#')
            continue;   /* empty line or comment line */
        if(strcasecmp(cmd, "set") == 0){
            int bit;
            if(!parseNumber(&p, &bit) || bit > 7)
                return PARSE_ERROR_ARGUMENT1;
            WRITE_ACTION(bit);
        }else if(strcasecmp(cmd, "clear") == 0){
            int bit;
            if(!parseNumber(&p, &bit) || bit > 7)
                return PARSE_ERROR_ARGUMENT1;
            WRITE_ACTION(0x40 | bit);
        }else if(strcasecmp(cmd, "set_pulse") == 0){
            int bit, duration;
            if(!parseNumber(&p, &bit) || bit > 7)
                return PARSE_ERROR_ARGUMENT1;
            if(!parseNumber(&p, &duration) || duration > 7)
                return PARSE_ERROR_ARGUMENT2;
            WRITE_ACTION((duration << 3) | bit);
        }else if(strcasecmp(cmd, "clear_pulse") == 0){
            int bit, duration;
            if(!parseNumber(&p, &bit) || bit > 7)
                return PARSE_ERROR_ARGUMENT1;
            if(!parseNumber(&p, &duration) || duration > 7)
                return PARSE_ERROR_ARGUMENT2;
            WRITE_ACTION(0x40 | (duration << 3) | bit);
        }else if(strcasecmp(cmd, "wait_input") == 0){
            int bit;
            if(!parseNumber(&p, &bit) || bit > 3)
                return PARSE_ERROR_ARGUMENT1;
            WRITE_ACTION(0x80 | bit);
        }else if(strcasecmp(cmd, "delay") == 0){
            int duration;
            if(!parseNumber(&p, &duration))
                return PARSE_ERROR_ARGUMENT1;
            while(duration > 0){
                if(duration >= 512){
                    int x = duration >> 9;
                    if(x > 15)
                        x = 15;
                    WRITE_ACTION(0xf0 | x);
                    duration -= x << 9;
                }else if(duration > 32){
                    int x = duration >> 5;
                    WRITE_ACTION(0xe0 | x);
                    duration -= x << 5;
                }else{
                    if(duration > 0){ /* don't encode zero time */
                        WRITE_ACTION(0xc0 | (duration - 1));
                        duration = 0;
                    }
                }
            }
        }else{
            return PARSE_ERROR_UNKNOWN_COMMAND;
        }
    }
    memset(data + i, 0xff, 512 - i);    /* fill remaining space */
    i -= 2; /* i is code length now */
    data[0] = i;
    data[1] = i >> 8;
    return 0;
}

/* ------------------------------------------------------------------------- */

char    *parserStrError(int err)
{
static char buffer[256];

    switch(err){
    case PARSE_ERROR_UNKNOWN_COMMAND:
        sprintf(buffer, "Unknown command in line %d", parserLineNr);
        break;
    case PARSE_ERROR_ARGUMENT1:
        sprintf(buffer, "Error parsing argument 1 in line %d", parserLineNr);
        break;
    case PARSE_ERROR_ARGUMENT2:
        sprintf(buffer, "Error parsing argument 2 in line %d", parserLineNr);
        break;
    case PARSE_ERROR_CODE_OVERFLOW:
        sprintf(buffer, "Code exceeds 510 bytes in line %d", parserLineNr);
        break;
    default:
        sprintf(buffer, "Unknown parse error in line %d", parserLineNr);
        break;
    }
    return buffer;
}

/* ------------------------------------------------------------------------- */
