#ifndef FUNCTION_HANDLER_H
#define FUNCTION_HANDLER_H

#include <stdio.h>
#include "bitmask_utils.h"

void turnOn(void *statusModule, void *name);
void turnOff(void *statusModule, void *name);
void checkModuleStatus(void *statusModule, void *name);



#endif // FUNCTION_HANDLER_H