#include <stdio.h>
#include <stdarg.h>

void test(int count, ...){
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        printf("value%d: %d\n", i + 1, va_arg(args, int));/* code */
    }   
    va_end(args);
}

int main(){
    test(4, 5, 7, 3, 4);
    return 0;
}