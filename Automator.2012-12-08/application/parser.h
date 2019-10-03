/* Name: parser.h
 * Project: Automator
 * Author: Christian Starkjohann
 * Creation Date: 2006-02-11
 * Tabsize: 4
 * Copyright: (c) 2006 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: Proprietary, free under certain conditions. See Documentation.
 * This Revision: $Id$
 */

#ifndef __parser_h_INCLUDED__
#define __parser_h_INCLUDED__

/*
General Description:
This module implements storing and loading of Automator program files in
plain text. This allows the user to modify programs by hand.
*/

#define PARSE_ERROR_UNKNOWN_COMMAND     1
#define PARSE_ERROR_ARGUMENT1           2
#define PARSE_ERROR_ARGUMENT2           3
#define PARSE_ERROR_CODE_OVERFLOW       4
/* error codes */

extern int  parserLineNr;
/* Line number of last line parsed */

void    parserWriteProgram(FILE *fp, char data[512]);
/* Writes a program to the file 'fp'.
 */
int     parserReadProgram(FILE *fp, char data[512]);
/* Reads a program from file 'fp'. Returns 0 on success, an error code
 * otherwise.
 */
char    *parserStrError(int err);
/* Tranlsates error codes to strings. The string is in a static buffer and is
 * only valid until the next call to parserStrError().
 */

#endif /* __parser_h_INCLUDED__ */
