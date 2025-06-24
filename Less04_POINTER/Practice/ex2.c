#include <stdio.h>

// truyền tham số vào hàm bằng con trỏ => thay đổi giá trị của biến thực sự
// truyền tham số vào hàm bằng giá trị => thay đổi giá trị của biến tạm

void swap1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap1(x, y);
    printf("After swap1: x = %d, y = %d\n", x, y);
    swap2(&x, &y);
    printf("After swap2: x = %d, y = %d\n", x, y);
    return 0;
}


