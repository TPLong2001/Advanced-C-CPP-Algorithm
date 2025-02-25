#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__, 'a')

int sum(int count, ...){

    va_list args;
    va_list args1;

    va_start(args, count);
    va_copy(args1, args);

    int sum = count;
    char *value;

    while ((value = va_arg(args1, char*)) != (char*)'a'){
        sum += va_arg(args, int);
    }   
    va_end(args);
    return sum;
}

int main(){
    printf("Sum: %d\n", tong(4, 5, 'b', 96, 97));
    // 97 = 'a' lên vẫn bị dừng ở  số 97 => sum = 4 + 5 + 98 + 96 = 203
    return 0;
}