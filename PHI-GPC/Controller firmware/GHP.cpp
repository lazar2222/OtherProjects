#include "GHP.h"

const byte DEVICE_ID = 53;

const byte ANALOG_CHANGE = 'A';
const byte BUTTON_PRESS = 'B';
const byte BUTTON_RELEASE = 'R';
const byte ENCODER_INCREMENT = 'I';
const byte ENCODER_DECREMENT = 'D';
const byte RESPONCE_PERSISTENT = 'r';
const byte RESPONCE_DISOVER = 'w';

const byte SYSTEM = 'S';
const byte SYSTEM_DISCOVER = 'W';
const byte SYSTEM_RESET = 'R';

const byte SET_LED = 'L';
const byte SET_LCD = 'l';
const byte SET_PERISTENT = 'P';
const byte GET_PERISTENT = 'p';

const byte SET_LED_LEN = 5;
const byte SET_LCD_LEN = 22;

byte MsgBuffer[25];
bool DoUpdateLcd=false;

void SendMessage(byte cmd,byte chan,short val,bool x)
{
    Serial.write(cmd);
    Serial.write(chan);
    Serial.write(lowByte(val));
    Serial.write(highByte(val));
}

void SendMessage(byte cmd,byte chan,byte val)
{
    Serial.write(cmd);
    Serial.write(chan);
    Serial.write(val);
}

void SendMessage(byte cmd,short chan)
{
    if(chan!=-1)
    {
        Serial.write(cmd);
        Serial.write(chan);
    }
}

void ReadSerial()
{
    if(Serial.available()>0)
    {
        MsgBuffer[0]=Serial.read();
        switch(MsgBuffer[0])
        {
            case SET_LED: {ParseL(); break;}
            case SET_LCD: {Parsel(); break;}
            case SYSTEM: {ParseS(); break;}
            case SET_PERISTENT: {ParseP(); break;}
            case GET_PERISTENT: {Parsep(); break;}
            default : { break;}
        }
    }
}

byte blockingRead()
{
    while (Serial.available()<1){}
    return Serial.read();
    
}

void blockingRead(byte* A,byte start,byte cnt)
{
    for (byte i = start; i < cnt+start; i++)
    {
        A[i]=blockingRead();
    }
    
}

void ParseL()
{
    blockingRead(MsgBuffer,1,4);
    for (byte i = 0; i < 3; i++)
    {
        LedValue[LedAlias[i][MsgBuffer[1]]][i]=MsgBuffer[i+2];
    }
}

void Parsel()
{
    blockingRead(MsgBuffer,1,21);
    for (byte i = 0; i < 20; i++)
    {
        LcdBuff[MsgBuffer[1]][i]=MsgBuffer[i+2];
    }
    LcdBuff[MsgBuffer[1]][20]='\0';
    DoUpdateLcd=true;
}

void ParseS()
{
    blockingRead(MsgBuffer,1,1);
    switch(MsgBuffer[1])
    {
        case SYSTEM_DISCOVER: {SendMessage(SYSTEM,RESPONCE_DISOVER,DEVICE_ID); Init=true; break;}
        case SYSTEM_RESET: {Lcd.clear();Lcd.print("RESET");delay(1000);software_Reset(); break;}
        default : { break;}
    }
}

void ParseP()
{
    blockingRead(MsgBuffer,1,2);
    WritePers(MsgBuffer[1],MsgBuffer[2]);
    RefreshPersistence();
}

void Parsep()
{
    blockingRead(MsgBuffer,1,1);
    SendMessage(RESPONCE_PERSISTENT,MsgBuffer[1],readPers(MsgBuffer[1]));
}