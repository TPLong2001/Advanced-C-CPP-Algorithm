#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    // Without register
    int i, sum = 0;
    start = clock();
    for (i = 0; i < 100000000; i++) {
        sum += i;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken without register: %f seconds\n", cpu_time_used);

    // With register
    register int j, reg_sum = 0;
    start = clock();
    for (j = 0; j < 100000000; j++) {
        reg_sum += j;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken with register: %f seconds\n", cpu_time_used);

    return 0;
}