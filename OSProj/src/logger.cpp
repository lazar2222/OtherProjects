#include "iostream.h"
#include "stdlib.h"

#include "logger.h"
#include "util.h"

void log(char* s,int level,int returnCode)
{
	if(level>=LOG_LEVEL)
	{
		INTDN();
		switch(level)
		{
		case LOG_LEVEL_INFO:{cout<< "INFO:"; break;}
		case LOG_LEVEL_WARNING:{cout<< "WARNING:"; break;}
		case LOG_LEVEL_ERROR:{cout<< "ERROR:"; break;}
		case LOG_LEVEL_CRITICAL:{cout<< "PANIC:"; break;}
		}
		cout<<s<<endl;
		if(level==LOG_LEVEL_CRITICAL)
		{
			exit(returnCode);
		}
		INTEN();
	}
}

void debug(char* s)
{
	log(s,LOG_LEVEL_INFO);
}

void warning(char* s)
{
	log(s,LOG_LEVEL_WARNING);
}

void error(char* s)
{
	log(s,LOG_LEVEL_ERROR);
}


void panic(char* s,int returnCode)
{
	log(s,LOG_LEVEL_CRITICAL,returnCode);
}
