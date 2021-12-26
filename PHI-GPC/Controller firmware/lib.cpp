#include "lib.h"

void SetMux(byte pins[],byte siz,byte val)
{
    byte mask=1;
    for(byte i=0;i<siz;i++)
    {
        digitalWrite(pins[i],((mask&val)>0)?HIGH:LOW);
        mask<<=1;
    }   
}

void SetMatrix(byte pins[],byte siz,byte val)
{
    for(byte i=0;i<siz;i++)
    {
        digitalWrite(pins[i],(i==val)?HIGH:LOW);
    }   
}

void SetMatrix(byte pins[],byte siz,byte val,bool inv)
{
    for(byte i=0;i<siz;i++)
    {
        digitalWrite(pins[i],(i==val)?LOW:HIGH);
    }   
}

void DoPinMode(byte pins[],byte siz,byte mode)
{
  for(byte i=0;i<siz;i++)
  {
    pinMode(pins[i],mode);  
  }  
}

void software_Reset()
{
  asm volatile (" jmp 0");
}
