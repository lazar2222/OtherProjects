#ifndef MYDEF
#define MYDEF

#include <arduino.h>
#include <LiquidCrystal.h>

const extern byte LCDRS, LCDEN, D4, D5, D6, D7;
const extern byte MUXE[];
const extern byte MUXQ[];
const extern byte MUXAR[];
const extern byte MUXDR[];
const extern byte MUXDW[]; 
const extern byte ENC[5][2];
const extern byte MATRIXB[];
const extern byte MATRIXD[];
const extern byte JOYX, JOYY, JOYS;
const extern byte PEDALA, PEDALO, PEDALT;

const extern byte JOYXI, JOYYI, JOYSI ;
const extern byte PEDALAI, PEDALOI, PEDALTI;
const extern byte AnalogAlias[];
const extern short ButtonAlias[];
const extern byte LedAlias[3][16];

extern LiquidCrystal Lcd;

extern bool Init;
extern volatile short ENCPre[5];
extern bool ENClast[5];
extern short AnalogPre[19];
extern short AnalogAvg[19];
extern byte ButtonDebounce[67];
extern bool ButtonBool[67];
extern byte LedValue[16][3];
extern char LcdBuff[4][21];

//Persistent
extern bool KRAFTWERK;
extern byte TRESHOLD;
extern byte DEBOUNCE;
extern byte ERF;
extern byte ENCMS;
extern byte APLL;
extern byte APUL;

#endif
