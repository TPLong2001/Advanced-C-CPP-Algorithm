#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

extern int exception;
extern jmp_buf buf;

#define TRY         if((exception = setjmp(buf)) == 0)
#define CATCH(x)    else if(exception == x)
#define THROW(x)    longjmp(buf, x)

#define WARNING  THROW(1)
#define ERROR    THROW(2)

void handleException(uint8_t sizeList, uint8_t **arrayStatus);

#endif // ERROR_HANDLER_H