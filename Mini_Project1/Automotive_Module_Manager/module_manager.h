#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "function_handler.h"

typedef union StatusModule{
    uint8_t allStatus;
    struct{
        uint8_t on : 1;
        uint8_t error : 1;
        uint8_t warning : 1;
    } Status;
}StatusModule;

typedef struct Module{
    int ID;
    char name[50];
    StatusModule statusModule;
    void (*controlAction)(void *, void *);
}Module;

extern Module *moduleList;
extern uint8_t sizeList;
extern uint8_t **arrayStatus;

void addModule(Module *module);
void deleteModule(int ID);

void turnOnModule(Module *module);
void turnOffModule(Module *module);

void moduleStatus(Module *module);
void displayModuleList();

void updateStatusList();
void exitSystem();

#endif // MODULE_MANAGER_H