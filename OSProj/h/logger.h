#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOG_LEVEL 3

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_CRITICAL 3

#define RETURN_CODE_DEFAULT -1
#define RETURN_CODE_OUTOFMEMORY -2

void log(char* s,int level,int returnCode=RETURN_CODE_DEFAULT);
void debug(char* s);
void warning(char* s);
void error(char* s);
void panic(char* s,int returnCode=RETURN_CODE_DEFAULT);

#endif
