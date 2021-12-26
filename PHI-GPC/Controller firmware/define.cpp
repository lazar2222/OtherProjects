#include "define.h"

const byte LCDRS = 49, LCDEN = 47, D4 = 45, D5 = 43, D6 = 41, D7 = 39;
const byte MUXE[] = {42,38,40};
const byte MUXQ[] = {26,32};
const byte MUXAR[] = {A2,A3};
const byte MUXDR[] = {34,36};
const byte MUXDW[] = {4,11,3}; 
const byte ENC[5][2] = {{21,33},{20,31},{19,27},{18,23},{2,46}};
const byte MATRIXB[] = {28,22,30,24};
const byte MATRIXD[] = {50,52,53,51};
const byte JOYX = A15, JOYY = A13, JOYS = A14;
const byte PEDALA = A0, PEDALO = 12, PEDALT = 13;

const byte JOYXI = 16, JOYYI = 17, JOYSI = 64;
const byte PEDALAI = 18, PEDALOI = 65, PEDALTI = 66;
const byte AnalogAlias[] = {15,10,8,13,5,7,2,1,0,4,6,3,11,9,12,14,16,17,18};
const short ButtonAlias[] = {49,51,50,48,32,36,44,40,-1,-1,-1,-1,33,37,45,41,-1,-1,-1,-1,34,38,46,42,-1,-1,-1,-1,35,39,47,43,14,12,13,15,29,28,31,30,10,8,9,11,25,24,27,26,6,4,5,7,21,20,23,22,2,0,1,3,17,16,19,18,52,54,53};
const byte LedAlias[3][16] = {{1,5,9,13,0,4,8,12,3,7,11,15,2,6,10,14},{1,5,9,13,3,7,11,15,2,6,10,14,0,4,8,12},{3,7,11,15,0,4,8,12,1,5,9,13,2,6,10,14}};

LiquidCrystal Lcd(LCDRS, LCDEN, D4, D5, D6, D7);

bool Init = false;
volatile short ENCPre[5] = {0};
bool ENClast[5] = {true};
short AnalogPre[19]={0};
short AnalogAvg[19]={0};
byte ButtonDebounce[67]={0};
bool ButtonBool[67]={false};
byte LedValue[16][3]={0};
char LcdBuff[4][21];

//Persistent
bool KRAFTWERK=false;
byte TRESHOLD=3;
byte DEBOUNCE=3;
byte ERF=80;
byte ENCMS=1;
byte APLL=60;
byte APUL=65;