#include <stdio.h>

int *ptr = NULL;

void increment() {
    static int count = 0; // static variable
    ptr = &count;
    count++;
    printf("Count: %d\n", count);
}

int main() {
    increment();
    increment();
    increment();

    *ptr = 99;
    increment();
    return 0;
}