#include "util.h"
#include "iostream.h"
#include "stdlib.h"
#include "logger.h"

volatile int dnesting=0;
volatile int lock=0;
volatile int nesting=0;
volatile unsigned psw;
volatile unsigned fls;

void INTEN()
{
	lock--;
	if(lock<0)
	{
		panic("lock<0");
	}
}

void INTDN()
{
	lock++;
}

void DREALINTEN()
{
	dnesting--;
	if(dnesting<0)
	{
		panic("dnesting<0");
	}
	if(dnesting==0)
	{
		asm{STI};
	}

}

void DREALINTDN()
{
	asm{CLI};
	dnesting++;
}

void REALINTEN()
{
	asm{pushf
		pop psw};

	if(psw&PSW_I)
	{
		panic("INTE n already enabled");
	}

	nesting--;
	if(nesting<0)
	{
		panic("nesting<0");
	}
	if(nesting==0 && fls)
	{
		asm{sti};
	}
}

void REALINTDN()
{
	asm{pushf
		pop psw};
	asm{CLI};
	if(nesting==0)
	{
		fls=psw&PSW_I;
	}
	nesting++;
}
