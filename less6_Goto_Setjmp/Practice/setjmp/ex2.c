#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

#define TRY         if ((exception = setjmp(buf)) == 0)
#define CATCH(num)  else if (exception == num)
#define THROW(num)  longjmp(buf, num)

int exception;

void functionThatThrows(int exceptionType) {
    printf("In functionThatThrows with exception type %d\n", exceptionType);
    THROW(exceptionType);
    printf("This will not be printed\n");
}

int main()
{
    TRY{
        printf("In try block\n");
        functionThatThrows(2);  // thay đổi giá trị này để thử các trường hợp khác nhau
        //functionThatThrows(3);
        printf("This will not be printed\n");
    }CATCH(1){
        printf("In catch block for exception 1\n");
    }CATCH(2){
        printf("In catch block for exception 2\n");
    }CATCH(3){
        printf("In catch block for exception 3\n");
    }else{
        printf("Unknown exception\n");
    }

    printf("After try-catch block\n");
    return 0;
}