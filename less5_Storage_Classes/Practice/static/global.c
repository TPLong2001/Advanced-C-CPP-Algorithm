#include <stdio.h>
#include "global.h"

static void say_hello() {  // Chỉ có trong utils.c
    printf("Hello, World!\n");
}

void call_say_hello() {  // Hàm public để gọi static function
    say_hello();
}
