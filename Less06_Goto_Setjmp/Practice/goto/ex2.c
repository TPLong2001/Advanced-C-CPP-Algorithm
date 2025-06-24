#include <stdio.h>

int main() {
    int i, j, k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (i == 2 && j == 3 && k == 1) {
                    goto end_loops;
                }
                printf("i = %d, j = %d, k = %d\n", i, j, k);
            }
        }
    }

end_loops:
    printf("Exited the loops at i = %d, j = %d, k = %d\n", i, j, k);

    return 0;
}
