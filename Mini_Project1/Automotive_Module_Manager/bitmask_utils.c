// Các hàm hỗ trợ xử lý bitmask
#include "bitmask_utils.h"

// quản lý trạng thái module: bật, tắt, lỗi, cảnh báo ( bitmask)
void setStatus(uint8_t *statusModule, uint8_t status){
    (*statusModule) |= status;
}

void clearStatus(uint8_t *statusModule, uint8_t status){
    (*statusModule) &= ~status;
}

uint8_t checkStatus(uint8_t *statusModule, uint8_t status){
    return (*statusModule) & status;
}