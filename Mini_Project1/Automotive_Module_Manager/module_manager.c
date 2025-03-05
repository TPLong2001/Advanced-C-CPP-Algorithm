// Xử lý danh sách module
#include "module_manager.h"

Module *moduleList = NULL;
uint8_t sizeList = 0;
uint8_t **arrayStatus = NULL;


static void addData(Module *module1, Module *module2){
    module1->ID = module2->ID;
    strcpy(module1->name, module2->name);
    module1->statusModule.allStatus = module2->statusModule.allStatus;
    module1->controlAction = module2->controlAction;
}

// Thêm module vào danh sách ( cấp phát động)
void addModule(Module *module){
    if(moduleList == NULL){
        sizeList = 1;
        // Cấp phát động cho mảng danh sách module
        moduleList = (Module*)malloc( sizeList * sizeof(Module));

        // Cấp phát động cho mảng 2 chiều lưu các trạng thái của danh sách module
        arrayStatus = (uint8_t **)malloc( sizeList * sizeof(uint8_t *));
        arrayStatus[0] = (uint8_t *)malloc(3 * sizeof(uint8_t));

        addData(&moduleList[sizeList - 1], module);         //moduleList[sizeList - 1] = module;
    }
    else{
        sizeList ++;
        // cập nhật mảng thêm phần tử
        moduleList = (Module*)realloc(moduleList, sizeList * sizeof(Module));

        // Cập nhật mảng thêm hàng
        arrayStatus = (uint8_t **)realloc(arrayStatus, sizeList * sizeof(uint8_t *));
        arrayStatus[sizeList - 1] = (uint8_t *)malloc(3 * sizeof(uint8_t));
        
        addData(&moduleList[sizeList - 1], module);     //moduleList[sizeList - 1] = module;
    }
}

// Xóa module khỏi danh sách array => lấy module cuối mảng bù vào vị trí xóa
void deleteModule(int ID){
    if(sizeList > 1){
        for(int i = 0; i < sizeList; i++){
            if(moduleList[i].ID == ID){
                // vị trí data cần xóa được thay thế bằng data cuối mảng
                addData(&moduleList[i], &moduleList[sizeList - 1]); //moduleList[i] = moduleList[sizeList - 1];
                
                // Cập nhật mảng xóa phần tử
                moduleList = (Module*)realloc(moduleList, (sizeList - 1) * sizeof(Module)); //update size

                // cập nhật mảng bớt hàng
                free(arrayStatus[sizeList - 1]);
                arrayStatus = (uint8_t **)realloc(arrayStatus, (sizeList - 1) * sizeof(uint8_t *));
                sizeList --;
                break;
            }
        }
    }else if(sizeList == 1){
        free(moduleList);
        free(arrayStatus[0]);
        free(arrayStatus);
        moduleList = NULL;
        arrayStatus = NULL;
        sizeList = 0;
    }
}

// Bật Module
void turnOnModule(Module *module){
    module->controlAction = turnOn;
    module->controlAction(&((module->statusModule).allStatus), module->name);
}

// Tắt module
void turnOffModule(Module *module){
    module->controlAction = turnOff;
    module->controlAction(&(module->statusModule.allStatus), module->name);
}

// Kiểm tra trạng thái module
void moduleStatus(Module *module){
    module->controlAction = checkModuleStatus;
    module->controlAction(&(module->statusModule.allStatus), module->name);
}



// Hiển thị 1 module
static void printModule(Module *module){
    const char *statusOn[] = {"OFF", "ON"};
    const char *statusError[] = {"NO ERROR", "ERROR"};
    const char *statusWarning[] = {"NO WARNING", "WARNING"};
    printf("Module %s\n", module->name);
    printf("ID: %d\n", module->ID);  
    printf("Status:\n");
    printf("\tON: %s\n", statusOn[(module->statusModule).Status.on]);
    printf("\tERROR: %s\n", statusError[(module->statusModule).Status.error]);
    printf("\tWARNING: %s\n", statusWarning[(module->statusModule).Status.warning]);
    printf("\n");
}

// Hiển thị danh sách module
void displayModuleList(){
    if(sizeList > 0){
        for(int i = 0; i < sizeList; i++){
            printf("Module %d\n", i + 1);
            printModule(&moduleList[i]);
        }
    }
}



// Kiểm tra từng trạng thái module
// Kiểm tra module bật không
static uint8_t moduleIsOn(Module *module){
    return module->statusModule.Status.on;
}
// Kiểm tra module lỗi không
static uint8_t moduleIsError(Module *module){
    return module->statusModule.Status.error;
}
// Kiểm tra module cảnh báo không
static uint8_t moduleIsWarning(Module *module){
    return module->statusModule.Status.warning;
}

// cập nhật danh sách trạng thái module
void updateStatusList(){
    for(uint8_t i = 0; i < sizeList; i++){
        arrayStatus[i][0] = moduleIsOn(&moduleList[i]);
        arrayStatus[i][1] = moduleIsError(&moduleList[i]);
        arrayStatus[i][2] = moduleIsWarning(&moduleList[i]);
    }
}


// Thoát hệ thống
void exitSystem(){

    // giải phóng moduleList
    free(moduleList);

    // giải phóng arrayStatus
    for(uint8_t i = 0; i < sizeList; i++){
        free(arrayStatus[i]);
    }
    free(arrayStatus);

    moduleList = NULL;
    arrayStatus = NULL;
    sizeList = 0;
}

// dùng setjmp/longjmp để xử lý lỗi khi module gặp lỗi


// tối ưu lưu trữ dữ liệu module bằng struct và union.

// Struct quản lý module: ID, name, status, access, controlAction

// Bitmask quản lý trạng thái module: STATUS_ON, STATUS_ERROR, STATUS_WARNING

// Function pointer thực hiện các hành động điều khiển module: bật/tắt, kiểm tra trạng thái module

// xử lý lỗi bằng setjmp/longjmp: gặp lỗi -> nhảy về trạng thái an toàn ( không dừng Ctrinh)



