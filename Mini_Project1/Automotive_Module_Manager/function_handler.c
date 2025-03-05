// Xử lý con trỏ hàm
#include "function_handler.h"

// sử dụng function pointer để thực hiện các hành động điều khiển module
void turnOn(void *statusModule, void *name){
    setStatus((uint8_t *)statusModule, (uint8_t)STATUS_ON);
    printf("Module %s is ON\n", (char *)name);
}

void turnOff(void *statusModule, void *name){
    clearStatus((uint8_t *)statusModule, (uint8_t)STATUS_ON);
    printf("Module %s is OFF\n", (char *)name);
}

void checkModuleStatus(void *statusModule, void *name){
    if(checkStatus((uint8_t *)statusModule, (uint8_t)STATUS_ERROR)){
        printf("Module %s is ERROR\n", (char *)name);
        // xử lý lỗi
    }

    if(checkStatus((uint8_t *)statusModule, (uint8_t)STATUS_WARNING)){
        printf("Module %s is WARNING\n", (char *)name);
        // xử lý cảnh báo
    }
    
    if(checkStatus((uint8_t *)statusModule, (uint8_t)STATUS_ON)){
        printf("Module %s is ON\n", (char *)name);
    }
    else{
        printf("Module %s is OFF\n", (char *)name);
    }
}
