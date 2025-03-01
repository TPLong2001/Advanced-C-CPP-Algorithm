#include "global.h"

int main() {
    say_hello();  // Lỗi: Không thể gọi được do static chỉ có tác dụng trong global.c
    return 0;
}


// gcc -c global.c -o global.o
// gcc -c main.c -o main.o
// gcc global.o main.o -o main
