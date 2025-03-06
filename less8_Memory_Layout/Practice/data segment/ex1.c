#include <stdio.h>

int global_init = 100;        // Data Segment (đã khởi tạo)
static int static_init = 200; // Data Segment (tĩnh và khởi tạo)
const char message[] = "Hi";  // Read-Only Data (hoặc có thể chung vùng Text)

int global_uninit;            // BSS Segment (chưa khởi tạo)
static int static_uninit;     // BSS Segment (tĩnh chưa khởi tạo)

int main() {
    printf("%d %d %s\n", global_init, static_init, message);
    return 0;
}

