#include <stdio.h>
#include <stdint.h>

//sizeof - kích thước con trỏ phụ thuộc vào Kiến trúc của máy tính và trình biên dịch
// 32 bit: 4 bytes
// 64 bit: 8 bytes
// 16 bit: 2 bytes


int main() {
    printf("Size of char pointer: %zu bytes\n", sizeof(char *));
    printf("Size of int pointer: %zu bytes\n", sizeof(int *));
    printf("Size of float pointer: %zu bytes\n", sizeof(float *));
    printf("Size of double pointer: %zu bytes\n", sizeof(double *));
    printf("Size of void pointer: %zu bytes\n", sizeof(void *));
    printf("Size of long pointer: %zu bytes\n", sizeof(long *));
    printf("Size of short pointer: %zu bytes\n", sizeof(short *));
    
    // Cú pháp khai báo con trỏ  <kiểu dữ liệu> *<tên con trỏ>;
    // Kiểu dữ liệu của con trỏ sẽ phụ thuộc vào kiểu dữ liệu của biến mà con trỏ trỏ tới
    // khi truy cập giá trị bằng con trỏ, kiểu dữ liệu con trỏ sẽ cho phép bạn truy cập giá trị đúng với kích thước của kiểu dữ liệu đó

    int x = 500;  //0b 00000001 11101000
    int *p = &x;
    uint8_t *c = (uint8_t*)p;       // con trỏ kiểu uint8_t trỏ tới địa chỉ của biến x
    uint8_t *d = (uint8_t*)p + 1;   // con trỏ kiểu uint8_t trỏ tới địa chỉ của biến x + 1 byte
    uint16_t *e = (uint16_t*)p;     // con trỏ kiểu uint16_t trỏ tới địa chỉ của biến x

    printf("Address of x: %p\n", p);
    printf("Value of x: %d\n", *p);
    printf("Value of x  1byte_Low: %d\n", *c); // 0b 11101000 - Lấy 1 byte đầu tiên của biến x
    printf("Value of x 1byte_High: %d\n", *d); // 0b 00000001 - Lấy 1 byte thứ 2 của biến x
    printf("Value of x 2byte: %d\n", *e);      // 0b 00000001 11101000 - Lấy 2 byte của biến x

    return 0;
}