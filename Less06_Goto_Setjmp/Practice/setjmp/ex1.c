#include <stdio.h>
#include <setjmp.h>

jmp_buf buffer;

void second() {
    printf("second\n");
    longjmp(buffer, 1);
}

void first() {
    second();
    printf("first\n"); // This line will not be executed
}

int main() {
    if (setjmp(buffer) == 0) {
        first();
    } else {
        printf("main\n");
    }
    return 0;
}