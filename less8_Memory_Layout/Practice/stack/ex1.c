#include <stdio.h>

void foo(int x) {
    int a = 10;         // Biến cục bộ → Stack
    int b = x + a;      // Biến cục bộ → Stack
    printf("%d\n", b);
}

void display(int x, const char *str) {
    const int local_const = 20;      // Biến hằng cục bộ → Stack

    int *ptr = &local_const;           // Con trỏ cục bộ → Stack (trỏ đến biến trong Stack)

    printf("x = %d\n", x);           // Tham số x → Stack
    printf("str = %s\n", str);       // Tham số str → Stack (trỏ đến vùng dữ liệu .rodata)
    printf("local_const = %d\n", local_const);
    *ptr = 10;
    printf("local_const = %d\n", local_const);
    printf("*ptr = %d\n", *ptr);     // Trỏ đến local_var
}

int main() {
    int number = 5;                  // Biến cục bộ → Stack
    foo(number);                     // Gọi hàm foo, đẩy num làm tham số vào Stack
    
    const char *message = "Hello";   // Con trỏ cục bộ → Stack (trỏ đến vùng .rodata)
    display(number, message);        // Truyền tham số vào Stack
    return 0;
}
