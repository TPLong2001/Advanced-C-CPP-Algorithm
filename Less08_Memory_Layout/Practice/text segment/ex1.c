/**
 * Hàm `hello` và hàm `main` được lưu trữ trong text segment.
 * text segment là một phần của bộ nhớ chương trình nơi chứa mã thực thi (các lệnh).
 * 
 * Các hàm được lưu trữ trong text segment:
 * - hello: In "Hello, World!" ra màn hình.
 * - main: Gọi hàm hello và trả về 0.
 */
#include <stdio.h>

const int MAX = 100;            // Read-Only Data (hoặc có thể chung vùng Text)

const char message[] = "Hi";    // Read-Only Data (hoặc có thể chung vùng Text)

char *str = "Hello, World!";    // "Hello, World!" (string literals)

void hello() {
    printf("%s\n", str);
}

int main() {
    hello();
    str[0] = 'B';               // error -> dừng ctrinh
    hello();
    return 0;
}
