#ifndef MYLIB
#define MYLIB

#include <arduino.h>

void SetMux(byte pins[],byte siz,byte val);

void SetMatrix(byte pins[],byte siz,byte val);
void SetMatrix(byte pins[],byte siz,byte val,bool inv);

void DoPinMode(byte pins[],byte siz,byte mode);

void software_Reset();

#endif
