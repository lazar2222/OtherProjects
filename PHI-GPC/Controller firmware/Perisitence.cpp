#include "Persistence.h"

const byte PERS_KAFTWERK = 0;
const byte PERS_TRESHOLD = 1;
const byte PERS_DEBOUNCE = 2;
const byte PERS_ERF = 3;
const byte PERS_ENCMS = 4;
const byte PERS_APLL = 5;
const byte PERS_APUL = 6;

void WritePers(byte ID,byte val)
{
    EEPROM.update(ID,val);
}

byte readPers(byte ID)
{
    return EEPROM.read(ID);
}

void RefreshPersistence()
{
    if(readPers(PERS_KAFTWERK)==255)
    {
        WritePers(PERS_KAFTWERK,KRAFTWERK);
        WritePers(PERS_TRESHOLD,TRESHOLD);
        WritePers(PERS_DEBOUNCE,DEBOUNCE);
        WritePers(PERS_ERF,ERF);
        WritePers(PERS_ENCMS,ENCMS);
        WritePers(PERS_APLL,APLL);
        WritePers(PERS_APUL,APUL);
    }
    KRAFTWERK = readPers(PERS_KAFTWERK);
    TRESHOLD = readPers(PERS_TRESHOLD);
    DEBOUNCE = readPers(PERS_DEBOUNCE);
    ERF = readPers(PERS_ERF);
    ENCMS = readPers(PERS_ENCMS);
    APLL = readPers(PERS_APLL);
    APUL = readPers(PERS_APUL);
}