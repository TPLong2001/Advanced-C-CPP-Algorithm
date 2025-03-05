#include "error_handler.h"

int exception;
jmp_buf buf;

// uint8_t arrayStatus[][3]
// arrayStatus[][0] -> status ON
// arrayStatus[][1] -> status ERROR
// arrayStatus[][2] -> status WARNING

void handleException(uint8_t sizeList, uint8_t **arrayStatus){
    uint8_t statusWarning = 0;
    if(sizeList > 0){
        for(int i = 0; i < sizeList; i++){
            if(arrayStatus[i][1]){
                printf("Module %d is ERROR\n", i);
                printf("Handling ERROR ...\n");
                ERROR;
            }
            else if(arrayStatus[i][2]){
                printf("Module %d is WARNING\n", i);
                statusWarning = 1;
            }
        }
    }
    if(statusWarning){
        WARNING;
    }
}
