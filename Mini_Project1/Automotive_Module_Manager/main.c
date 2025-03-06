// Chương trình chính

#include "module_manager.h"
#include "error_handler.h"

int main(){
    uint8_t exit = 0;
BEGIN:
    Module module1 = {1, "ECU", 0, NULL};
    Module module2 = {2, "ABS", 0, NULL};
    Module module3 = {3, "LIGHT", 0, NULL};
    Module module4 = {4, "AIR CONDITIONER", 0, NULL};
    Module module5 = {5, "TEMPERATURE SENSOR", 0, NULL};

    addModule(&module1);
    addModule(&module2);
    addModule(&module3);
    addModule(&module4);
    addModule(&module5);

    turnOnModule(&moduleList[0]);
    turnOnModule(&moduleList[1]);
    turnOnModule(&moduleList[2]);
    turnOnModule(&moduleList[3]);
    turnOnModule(&moduleList[4]);

    // moduleStatus(&moduleList[0]);
    // moduleStatus(&moduleList[1]);
    // moduleStatus(&moduleList[2]);
    while (1)
    {
        // làm việc với module
        printf("Working with module ...\n");
        
        setStatus(&moduleList[0].statusModule.allStatus, STATUS_WARNING);
        setStatus(&moduleList[1].statusModule.allStatus, STATUS_ERROR);  

        displayModuleList();

        TRY{                                            // bắt đầu xử lý ngoại lệ
            printf("Checking module status ...\n");
            updateStatusList();

            handleException(sizeList, arrayStatus);
        }
        CATCH(1){                                       // cảnh báo
            // xử lý cảnh báo
        }CATCH(2){ // lỗi
            goto OUT;
        }
    }

OUT:
    exitSystem();

    if(!exit){
        goto BEGIN;
    }

    return 0;
}