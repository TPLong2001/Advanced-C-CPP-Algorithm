#include <stdio.h>
//VD1: sử dụng file.c thông qua include
//#include "file.c"

//VD2: sử dụng file.c thông qua prototype
// extern int var_global;
// extern void display();
// // sử dụng terminal/cmd : gcc main.c file.c -o main để link với file.c

//VD3: sử dụng file.h
#include "file.h"

int main() {
    display();  // sử dụng hàm display từ file.c
    return 0;
}
//gcc main.c file.c -o main 

