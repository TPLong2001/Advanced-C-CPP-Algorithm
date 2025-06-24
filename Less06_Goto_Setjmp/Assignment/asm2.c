#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;
char *error_message;

#define TRY         if((exception = setjmp(buf)) == 0)
#define CATCH       else
#define THROW(x,y)  throw(x,y)

typedef enum ErrorCodes { 
    NO_ERROR            = 0, 
    FILE_ERROR          = 1, 
    NETWORK_ERROR       = 2, 
    CALCULATION_ERROR   = 3
} ErrorCodes;

void throw(ErrorCodes error, char *code){
    if(error != NO_ERROR ){
        error_message = code;
    }
    longjmp(buf, error);
}

void readFile() {
    printf("Reading file...\n");
    THROW(FILE_ERROR, "File Error: File not found.");
}

void networkOperation() {
    printf("Processing network...\n");
    THROW(NETWORK_ERROR, "Network Error: No connection.");
}

void calculateData() {
    printf("Calculating data...\n");
    THROW(CALCULATION_ERROR, "Calculation Error: Empty data.");
}

int main(){
    TRY{
        readFile();
        networkOperation();
        calculateData();
    }CATCH{ // all CATCH 
        printf("%s\n", error_message);
    } 

    return 0;
}
