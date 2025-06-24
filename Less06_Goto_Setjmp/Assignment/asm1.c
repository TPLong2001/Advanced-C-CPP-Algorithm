#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;
char *error_code;

#define TRY         if((exception = setjmp(buf)) == 0)
#define CATCH       else
#define THROW(x,y)    throw(x,y)

void throw(int x, char *code){

    if(x != 0 ){
        error_code = code;
    }
    longjmp(buf, x);
}

double divide(double a, double b) {
    if (b == 0) {
        THROW(1, "Lỗi: Phép chia cho 0!");
    }
    THROW(2, "Lỗi: Những lỗi khác!");
    return a / b;
}

int main(){
    double div;
    TRY{
        div = divide(5, 1);
    }CATCH{
        printf("%s\n", error_code);
    }

    return 0;

}