#ifndef BITMASK_UTILS_H
#define BITMASK_UTILS_H


#include <stdint.h>

#define STATUS_ON        (1 << 0)  // Module đang bật
#define STATUS_ERROR     (1 << 1)  // Module gặp lỗi
#define STATUS_WARNING   (1 << 2)  // Cảnh báo lỗi

void setStatus(uint8_t *statusModule, uint8_t status);
void clearStatus(uint8_t *statusModule, uint8_t status);
uint8_t checkStatus(uint8_t *statusModule, uint8_t status);

#endif // BITMASK_UTILS_H