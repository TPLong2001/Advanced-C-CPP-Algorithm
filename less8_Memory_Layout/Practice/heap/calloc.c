#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    ptr = (int *)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);  // Sẽ in ra toàn số 0
    }
    printf("\n");

    free(ptr);
    return 0;
}
