#ifndef _UTIL_H_
#define _UTIL_H_

#include <_null.h>
#include <dos.h>

#define TRUE 1
#define FALSE 0
#define PSW_I 0x200

extern volatile int lock;

void INTEN();
void INTDN();
void REALINTEN();
void REALINTDN();
void DREALINTEN();
void DREALINTDN();

#endif
