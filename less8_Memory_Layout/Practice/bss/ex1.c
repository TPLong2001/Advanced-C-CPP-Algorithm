#include <stdio.h>

// Uninitialized global variable
int global_var;             // BSS Segment (toàn cục chưa khởi tạo)  

 // Uninitialized static variable
static int static_var;      // BSS Segment (static chưa khởi tạo)

int main() {
   
    printf("Value of uninitialized global variable: %d\n", global_var);
    printf("Value of uninitialized static variable: %d\n", static_var);

    return 0;
}