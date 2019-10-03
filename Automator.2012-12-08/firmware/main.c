/* Name: main.c
 * Project: Automator
 * Author: Christian Starkjohann
 * Creation Date: 2005-12-29
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: Proprietary, free under certain conditions. See Documentation.
 * This Revision: $Id$
 */

/* #define INVERT_RELAYS        used during debugging on evaluation board */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <stdlib.h>

#include "usbdrv.h"
#include "oddebug.h"


#define EVNT_MERGE_TIME 3   /* clock range for input synchronicity */

static uchar    recording;      /* bitmask of bits which are recorded */
static uchar    recordKeyHeld;
static int      beepCnt;

/* variables for recording: */
static struct{
    unsigned    size;
    uchar       data[510];
}               code;
static unsigned actionTime;     /* how long this action already lasts */

/* variables for playback: */
static unsigned codeReadPos;            /* offset in data[] array in eeprom */
static unsigned codeEepromSize;         /* number of code bytes in eeprom */
static unsigned actionTimeRemaining;    /* ticks remaining in current action */
static uchar    outputStatus;           /* output bits */
static uchar    recentEvents[4];        /* not-0 for recently received events */

/* The following table generates a logarithmic time scale in the range 10ms to
 * 2 seconds from a 128 step analog input. It was generated with the awk script
 * awk 'BEGIN{cnt=128;f=exp(log(23438/117)/(cnt-1));x=117;for(i=0;i<cnt;i++){
 * printf("%5.0f, ", x); x*=f} printf("\n");}'
 */
static const unsigned   timerVals[128] PROGMEM = {
      117,   122,   127,   133,   138,   144,   150,   157,
      163,   170,   178,   185,   193,   201,   210,   219,
      228,   238,   248,   259,   270,   281,   293,   306,
      319,   332,   346,   361,   376,   392,   409,   427,
      445,   464,   484,   504,   526,   548,   571,   596,
      621,   648,   675,   704,   734,   765,   798,   832,
      867,   904,   943,   983,  1025,  1068,  1114,  1161,
     1211,  1263,  1316,  1372,  1431,  1492,  1555,  1622,
     1691,  1763,  1838,  1916,  1998,  2083,  2172,  2265,
     2361,  2462,  2567,  2676,  2790,  2909,  3033,  3162,
     3297,  3437,  3584,  3737,  3896,  4062,  4235,  4415,
     4604,  4800,  5004,  5217,  5440,  5672,  5913,  6165,
     6428,  6702,  6988,  7285,  7596,  7920,  8257,  8609,
     8976,  9358,  9757, 10173, 10606, 11058, 11530, 12021,
    12533, 13067, 13624, 14205, 14810, 15441, 16099, 16785,
    17501, 18246, 19024, 19835, 20680, 21561, 22480, 23438
};

/* ----------------------- hardware I/O abstraction ------------------------ */

/* pin assignments:
PB0 relais0
PB1 relais1
PB2 relais2
PB3 relais3 (mosi)
PB4 relais4 (miso)
PB5 relais5 (sck)

PC0 evnt0
PC1 evnt1
PC2 evnt2
PC3 evnt3
PC4 Speed (analog)
PC5 -- spare --

PD0 USB-
PD1 debug tx / status LED
PD2 USB+ = USB intr
PD3 enable relais (use internal pullup as current limiter)
PD4 key "record/stop"   [used in combination with "all" or an output]
PD5 key "all"
PD6 relais6
PD7 relais7

user interface:
press record
    -> if recording: save, clear recording
    -> reset playback
hold record
    -> disable relays
    -> listen for "all" and output keys, collect all keys
release record
    -> enable relays
    -> if key collected: set record

*/

static void setOutput(uchar data)
{
uchar   ddrdp, ddrd;

/* Outputs are kind of "PNP open collector" to allow wired-or with switches
 * for manual programming.
 */
    if(recordKeyHeld){
        data = recording;
    }else{
        data &= ~recording; /* mask out bits which are recorded */
    }
#ifdef INVERT_RELAYS
    PORTB = ~data;
#else
    PORTB = data;
#endif
    DDRB = 0x3f;    /* short low-Z pulse for low pins */
    DDRB = data;
    data &= 0xc0;
    ddrdp = DDRD | 0xc0;
    ddrd = (DDRD & 0x3f) | data;
#ifdef INVERT_RELAYS
    PORTD = (PORTD & 0x3f) | (~data & 0x3f);
#else
    PORTD = (PORTD & 0x3f) | data;
#endif
    DDRD = ddrdp;   /* short low-Z pulse for low pins */
    DDRD = ddrd;
}

static uchar getInput(void)
{
    return ~PINC & 0xf;
}

static uchar getOutput(void)
{
uchar   val;

    val = PINB & 0x3f;
    val |= PIND & 0xc0;
#ifdef INVERT_RELAYS
    val = ~val;
#endif
    return val;
}

static uchar getResetRecordKey(void)
{
    return (PIND & 0x10) == 0;
}

static uchar getStopKey(void)
{
    return (PIND & 0x20) == 0;
}

static void beep(uchar duration)
{
    beepCnt = duration * 200;
    TIMSK |= 1 << OCIE2;
}

ISR(TIMER2_COMP_vect, ISR_NOBLOCK)  /* run with global interrupt enable */
{
    if(--beepCnt <= 0){
        TIMSK &= ~(1 << OCIE2);
        PORTD |= 2;     /* make sure LED is off */
    }else{
        if(beepCnt & 1){
            PORTD |= 2;
        }else{
            PORTD &= ~2;
        }
    }
}

static void toggleLed(void)
{
    PORTD ^= 2;
}

static void setLed(uchar status)
{
    if(status){
        PORTD &= ~2;
    }else{
        PORTD |= 2;
    }
}

static void setRelayEnable(uchar enabled)
{
    if(enabled){
        DDRD &= ~0x08;  /* 0000 1000 bin -> make input */
        PORTD |= 0x08;  /* enable pullup */
    }else{
        PORTD &= ~0x08; /* disable pullup */
        DDRD |= 0x08;   /* make output */
    }
}

static void initHardware(void)
{
uchar   i, j;

    DDRC = 0;
    PORTC = 0x20;
    DDRD = 0x07;    /* 0000 0111 bin includes USB reset */
    PORTD = 0x3a;   /* 0011 1010 bin */
    setOutput(outputStatus);
    j = 0;
    while(--j){         /* USB Reset by device only required on Watchdog Reset */
        i = 0;
        while(--i);     /* delay >10ms for USB reset */
    }
    DDRD = 0x02;    /* 0000 0010 bin remove USB reset condition */
    /* ADC used for clock speed input: */
    ADMUX = 0x44;   /* ref=AVcc, select PC4 */
    ADCSRA = 0xc7;  /* enable ADC, start conversion, rate = 1/128 */
    /* Timer0 used to sample input (~50Hz) */
    TCCR0 = 5;  /* prescaler = 1024 */
    /* Timer1 used for event clock */
    TCCR1A = 0; /* normal mode, no output actions */
    TCCR1B = 0x08 | 5;  /* CTC mode, clear on OCR1A, prescaler = 1024 */
    OCR1A = 0xffff;
    /* Timer2 used for acoustic signaling, we want 2kHz interrupt rate */
    TCCR2 = 0x08 | 3;   /* CTC mode, prescaler = 32 */
    OCR2 = 188;
}

/* ------------------------------------------------------------------------- */

static void actionStart(uchar action)
{
    DBG1(0x10, &action, 1);
    switch(action & 0xc0){
    case 0:     /* set bit: 0 0 T T T B B B */
    case 0x40:{ /* clear bit: 0 1 T T T B B B */
        uchar bit = action & 7;
        uchar time = (action >> 3) & 7;
        actionTimeRemaining = time;
        if(action & 0x40){
            outputStatus &= ~(1 << bit);
        }else{
            outputStatus |= 1 << bit;
        }
        setOutput(outputStatus);
        break;}
    case 0x80:  /* wait for evnt: 1 0 0 0 0 0 B B */
        actionTimeRemaining = 0;
        break;
    case 0xc0:  /* delay: 1 1 U U T T T T */
        switch(action & 0x30){
        case 0:
        case 0x10:
            actionTimeRemaining = (action & 0x1f) + 1;
            break;
        case 0x20:
            actionTimeRemaining = (unsigned)(action & 0xf) << 5;
            break;
        case 0x30:
            actionTimeRemaining = (unsigned)(action & 0xf) << 9;
            break;
        }
        break;
    }
}

static uchar    actionEnd(uchar action)
{
    DBG1(0x11, &action, 1);
    switch(action & 0xc0){
    case 0:     /* set bit: 0 0 T T T B B B */
    case 0x40:{ /* clear bit: 0 1 T T T B B B */
        uchar time = (action >> 3) & 7;
        if(time != 0){
            uchar bit = action & 7;
            if(action & 0x80){
                outputStatus |= 1 << bit;
            }else{
                outputStatus &= ~(1 << bit);
            }
            setOutput(outputStatus);
        }
        break;}
    case 0x80:{ /* wait for evnt: 1 0 0 0 0 0 B B */
        uchar bit = action & 3;
        if(recentEvents[bit]){
            recentEvents[bit] = 0;
        }else{
            return 0;   /* don't allow end of action, still waiting for event */
        }
        break;}
    case 0xc0:  /* delay: 1 1 U U T T T T */
        break;
    }
    return 1;   /* allow end of action */
}

static void pollAction(void)
{
    if(codeEepromSize > 0 && actionTimeRemaining == 0 && !recordKeyHeld){   /* advance to next action */
        uchar allowEnd = 1;
        if(codeReadPos < codeEepromSize)
            allowEnd = actionEnd(eeprom_read_byte((uchar *)2 + codeReadPos));
        if(allowEnd){
            if(++codeReadPos >= codeEepromSize){
                if(recording){
                    codeReadPos = codeEepromSize;
                    return; /* dead-end here, wait for stop/reset key */
                }
                codeReadPos = 0;    /* start over again */
            }
            actionStart(eeprom_read_byte((uchar *)2 + codeReadPos));
        }
    }
}

/* ------------------------------------------------------------------------- */

#define EVNT_OUTPUT_SET 0
#define EVNT_OUTPUT_CLR 1
#define EVNT_INPUT      2
#define EVNT_STOP       3

static void writeAction(uchar action)
{
    DBG1(0x20, &action, 1);
    if(code.size < sizeof(code.data)){
        code.data[code.size++] = action;
    }else{
        beep(5);
    }
}

static void writeTime(unsigned time)
{
    while(time > 0){
        if(time >= 512){
            uchar x = time >> 9;
            if(x > 15)
                x = 15;
            writeAction(0xf0 | x);
            time -= (unsigned)x << 9;
        }else if(time > 32){
            uchar x = time >> 5;
            writeAction(0xe0 | x);
            time -= (unsigned)x << 5;
        }else{
            if(time > 0){ /* don't encode zero time */
                writeAction(0xc0 | (uchar)(time - 1));
                time = 0;
            }
        }
    }
}

static void recordEvent(uchar type, uchar value)
{
uchar   lastEvnt = 0xff;

    if(code.size > 0)
        lastEvnt = code.data[code.size-1];
    switch(type){
    case EVNT_OUTPUT_SET:
    case EVNT_OUTPUT_CLR:
        if(actionTime < 8 && (lastEvnt & 7) == value && (lastEvnt & (7<<3)) == 0){ /* there is potential for optimization */
            uchar lastType = lastEvnt & 0xc0;
            if((lastType == 0x40 && type == EVNT_OUTPUT_SET) || (lastType == 0x00 && type == EVNT_OUTPUT_CLR)){
                /* yes, this can be optimized! */
                if(actionTime == 0){
                    code.size--;    /* remove last event -- it was too short */
                }else{
                    lastEvnt |= (uchar)actionTime << 3;
                }
                code.data[code.size-1] = lastEvnt;
                break;
            }
        }
        writeTime(actionTime);
        writeAction((type << 6) | value);
        break;
    case EVNT_INPUT:
        /* don't care about time */
        writeAction(0x80 | value);
        break;
    case EVNT_STOP:
        writeTime(actionTime);
        break;
    }
    actionTime = 0;
}

static void saveCode(void)
{
    DBG1(0x21, 0, 0);
    wdt_disable();
    eeprom_write_block(&code, 0, code.size + sizeof(code.size));
    wdt_enable(WDTO_2S);
    codeEepromSize = code.size;
    DBG1(0x22, 0, 0);
}

static void pollInput(void)
{
uchar           i, mask, chg, val = getInput();
static uchar    inputMirror;    /* mirror of input bits to detect changes */

    chg = inputMirror ^ val;
    inputMirror = val;
    chg &= val;             /* only use rising edge */
    mask = 1;
    for(i=0;i<4;i++){
        if(chg & mask){
            DBG1(0x30, &i, 1);
            recentEvents[i] = EVNT_MERGE_TIME;
            if(recording)
                recordEvent(EVNT_INPUT, i);
        }
        mask <<= 1;
    }
}

static void pollOutput(void)
{
uchar           i, mask, chg, val = getOutput();
static uchar    outputMirror;   /* mirror of output bits to detect changes */

    chg = outputMirror ^ val;
    outputMirror = val;
    mask = 1;
    for(i=0;i<8;i++){
        if(chg & mask){
            DBG1(0x31, &i, 1);
            if(recordKeyHeld){
                if(val & mask){ /* rising edge only */
                    recording ^= mask;
                    DBG1(0x32, &recording, 1);
                    setOutput(outputStatus);
                }
            }else if(recording){
                recordEvent((val & mask) ? EVNT_OUTPUT_SET : EVNT_OUTPUT_CLR, i);
            }
        }
        mask <<= 1;
    }
}

static void resetPlayback(void)
{
uchar   i;

    codeReadPos = 0xffff;
    actionTimeRemaining = 0;
    outputStatus = 0;
    setOutput(outputStatus);
    for(i=0;i<4;i++)
        recentEvents[i] = 0;
    setLed(0);
}

static void startRecording(void)
{
    setOutput(outputStatus);
    pollOutput();
    code.size = 0;  /* reset recording pointer */
    actionTime = 0;
}

static void stopRecording(void)
{
    DBG1(0x42, 0, 0);
    recordEvent(EVNT_STOP, 0);
    recording = 0;
    setOutput(outputStatus);
    saveCode();
    beep(1);
    resetPlayback();
}

static void pollCommands(void)
{
static uchar    clearMirror;
uchar           val, chg;

    val = getStopKey();
    chg = clearMirror ^ val;
    clearMirror = val;
    chg &= val;     /* rising edge only */
    if(chg){        /* stop/clear recording */
        if(recordKeyHeld){
            DBG1(0x40, 0, 0);
            recording = 0;
            setOutput(outputStatus);
        }else if(recording){
            stopRecording();
        }
    }
    val = getResetRecordKey();
    chg = recordKeyHeld ^ val;
    recordKeyHeld = val;
    if(chg){
        DBG1(0x41, &val, 1);
        if(val){    /* record key pressed */
            setRelayEnable(0);  /* turn off relays */
            recording = 0;
            setOutput(outputStatus);
        }else{
            setRelayEnable(1);  /* enable relays */
            if(recording)
                startRecording();
        }
        resetPlayback();
    }
}

static void pollAdc(void)
{
static int  lastVal;
static char isInitialized;

    if((ADCSRA & 0x40) == 0){   /* conversion ready */
        int val = ADC;
        ADCSRA |= 0x40; /* start next conversion */
        if(abs(val - lastVal) > 6 || !isInitialized){
            isInitialized = 1;
            DBG2(0x50, (void *)&val, sizeof(val));
            lastVal = val;
            val = pgm_read_word(timerVals + ((val >> 3) & 0x7f));
            OCR1A = val;
            DBG1(0x51, (void *)&val, sizeof(val));
            if((unsigned)TCNT1 >= (unsigned)val)
                TCNT1 = 0;
        }
    }
}

/* ------------------------------------------------------------------------- */

/* we want the following clock range for action timing:
 *  min 50ms
 *  max 2s
 * in logarithmic scale in 256 steps
 * -> 1ms resolution required.
 */

static void timerInterrupt(void)
{
uchar   i;

    DBG2(0x01, 0, 0);
    if(recording || recordKeyHeld){
        toggleLed();
    }
    if(actionTimeRemaining)
        actionTimeRemaining--;
    if(actionTime != 0xffff)
        actionTime++;
    for(i=0;i<4;i++){
        if(recentEvents[i])
            recentEvents[i]--;
    }
}

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB Interface ----------------------------- */
/* ------------------------------------------------------------------------- */

static unsigned usbAddress;     /* current pointer for EEPROM address */
static uchar    usbReadLen;
static uchar    usbWriteLen;

#define LOWBYTE(var)    (((uchar *)&(var))[0])
#define HIGHBYTE(var)   (((uchar *)&(var))[1])

const PROGMEM char usbHidReportDescriptor[33] = {   /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x95, 0x02,                    //   REPORT_COUNT (2)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x95, 0x80,                    //   REPORT_COUNT (128)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};

uchar   usbFunctionRead(uchar *data, uchar len)
{
uchar   total;

    if(len > usbReadLen)
        len = usbReadLen;
    total = len;
    if(usbReadLen == 129){  /* first byte is report ID */
        usbReadLen--;
        len--;
        *data++ = 2;    /* report *D */
    }
    eeprom_read_block(data, (uchar *)0 + usbAddress, len);
    usbAddress += len;
    usbReadLen -= len;
    return total;
}

/* Writing to the EEPROM may take 7 * 8.5ms = 59.9ms which is slightly more
 * than the allowable <50ms. We usually get away with that.
 */
uchar   usbFunctionWrite(uchar *data, uchar len)
{
    if(usbWriteLen == 0)
        return 1;
    if(usbWriteLen == 0xff){    /* expecting address */
        usbWriteLen = 0;
        if(len < 3)
            return 0xff;        /* stall */
        LOWBYTE(usbAddress) = data[1];
        HIGHBYTE(usbAddress) = data[2];
        return 1;
    }
    if(usbWriteLen == 129){ /* first byte is report ID */
        data++;
        len--;
        usbWriteLen--;
    }
    if(len > usbWriteLen)
        len = usbWriteLen;
    eeprom_write_block(data, (uchar *)0 + usbAddress, len);
    if(usbAddress < 2){
        codeEepromSize = eeprom_read_word(0);   /* refresh RAM copy of code size */
        if(codeEepromSize > sizeof(code.data))
            codeEepromSize = 0;
    }
    usbAddress += len;
    usbWriteLen -= len;
    if(usbAddress >= 512){  /* hit end of memory */
        resetPlayback();
    }
    return usbWriteLen == 0;
}

uchar   usbFunctionSetup(uchar data[8])
{
static uchar    replyBuf[3];
usbRequest_t    *rq = (void *)data;

    usbMsgPtr = replyBuf;
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            if(rq->wValue.bytes[0] == 1){   /* ReportID "GET ADDRESS" */
                replyBuf[0] = rq->wValue.bytes[0];
                replyBuf[1] = LOWBYTE(usbAddress);
                replyBuf[2] = HIGHBYTE(usbAddress);
                return 3;
            }else if(rq->wValue.bytes[0] == 2){ /* ReportID "GET 128 bytes block" */
                usbReadLen = 129;
                return 0xff;                /* use usbFunctionRead() */
            }
        }else if(rq->bRequest == USBRQ_HID_SET_REPORT){
            if(rq->wValue.bytes[0] == 1){   /* ReportID "SET ADDRESS" */
                usbWriteLen = 0xff;         /* indicates "address" */
                return 0xff;                /* use usbFunctionWrite() */
            }else if(rq->wValue.bytes[0] == 2){ /* ReportID "SET 128 bytes block" */
                usbWriteLen = 129;
                return 0xff;                /* use usbFunctionWrite() */
            }
        }
    }else{
        if(data[1] == 0){       /* ECHO, for testing */
            replyBuf[0] = data[2];
            replyBuf[1] = data[3];
            return 2;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------------- */

int main(void)
{
    wdt_enable(WDTO_2S);
    initHardware();
    odDebugInit();
    usbInit();
    sei();
    beep(1);
    codeEepromSize = eeprom_read_word(0);
    if(codeEepromSize > sizeof(code.data))
        codeEepromSize = 0;
    pollInput();
    resetPlayback();
    DBG1(0x00, (void *)&codeEepromSize, sizeof(codeEepromSize));
    for(;;){    /* main event loop */
        wdt_reset();
        usbPoll();
        if(TIFR & (1 << OCF1A)){
            TIFR |= 1 << OCF1A; /* clear pending flag */
            timerInterrupt();
        }
        pollAction();
        if(TIFR & (1 << TOV0)){ /* debounce by sampling with reduced rate */
            TIFR |= 1 << TOV0;
            pollInput();
            pollOutput();
            pollCommands();
        }
        pollAdc();
    }
    return 0;
}

/* ------------------------------------------------------------------------- */
