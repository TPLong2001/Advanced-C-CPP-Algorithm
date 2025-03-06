#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;                          // Con trỏ cục bộ (Stack)
    int n = 5;                         // Biến cục bộ (Stack)

    // Cấp phát động vùng nhớ cho 5 số nguyên trên vùng nhớ Heap
    ptr = (int *)malloc(n * sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Thoát nếu cấp phát thất bại
    }

    // // Gán giá trị cho vùng nhớ trên Heap
    // for (int i = 0; i < n; i++) {
    //     ptr[i] = i + 1;
    // }

    // In giá trị
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    free(ptr); // Giải phóng vùng nhớ Heap
    return 0;
}
