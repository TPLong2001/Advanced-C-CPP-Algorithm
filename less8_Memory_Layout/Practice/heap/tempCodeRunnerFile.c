#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    ptr = (int *)malloc(n * sizeof(int));
    if (ptr == NULL) {
        printf("Initial allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        ptr[i] = i + 1;
    }

    // Mở rộng vùng nhớ lên 10 phần tử
    ptr = (int *)realloc(ptr, 10 * sizeof(int));
    if (ptr == NULL) {
        printf("Reallocation failed.\n");
        return 1;
    }

    for (int i = n; i < 10; i++) {
        ptr[i] = (i + 1) * 10;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    free(ptr);
    return 0;
}
