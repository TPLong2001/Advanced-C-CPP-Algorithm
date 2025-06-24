#include <stdio.h>

struct Example {
    char a;        // 1 byte
    // Thêm 3 byte đệm để căn chỉnh `b` sao cho bắt đầu tại địa chỉ chia hết cho 4
    int b;         // 4 byte
    char c;        // 1 byte
    // Thêm 7 byte đệm để căn chỉnh `d` sao cho bắt đầu tại địa chỉ chia hết cho 8
    double d;      // 8 byte
    short e;       // 2 byte
    // Thêm 6 byte đệm để tổng kích thước của struct là bội số của phần tử có căn chỉnh lớn nhất (8 byte)
};

int main() {
    struct Example ex;
    printf("Kích thước của struct Example: %lu byte\n", sizeof(ex));
    return 0;
}
