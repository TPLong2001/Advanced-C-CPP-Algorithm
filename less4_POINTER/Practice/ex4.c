#include <stdio.h>

// Function declarations
void add(int a, int b);
void subtract(int a, int b);
void multiply(int a, int b);

// Function pointer type
typedef void (*operation)(int, int);

// Function pointer callback
void calculate(operation op, int a, int b) {
    op(a, b);
}

// Function pointer to get operation
operation get_operation(char op) {
    switch (op) {
        case '+':
            return add;
        case '-':
            return subtract;
        case '*':
            return multiply;
        default:
            return NULL;
    }
}

int main() {
    // Array of function pointers
    printf("Array of function pointers\n");
    operation operations[3] = {add, subtract, multiply};
    //void (*operations[3])(int, int) = {add, subtract, multiply};

    for (int i = 0; i < 3; i++) {
        operations[i](5, 3);
    }


    // Function pointers
    printf("\nFunction pointers\n");
    void (*op1)(int, int) = &add;       //operation op1 = &add;
    operation op2 = &subtract;
    operation op3 = &multiply;

    op1(5, 3); // Calls add(5, 3)
    op2(5, 3); // Calls subtract(5, 3)
    op3(5, 3); // Calls multiply(5, 3)


    // Using function pointer callback
    printf("\nUsing function pointer as argument\n");
    calculate(add, 5, 3);
    calculate(subtract, 5, 3);
    calculate(multiply, 5, 3);


    // Using function pointer to get operation
    printf("\nUsing function pointer to get operation\n");
    operation op;
    op = get_operation('+');        // op = add
    if(op != NULL) {
        op(5, 3);                   // Calls add(5, 3)
    }else{
        printf("Invalid operation\n");
    }

    op = get_operation('-');        // op = subtract
    if(op != NULL) {
        op(5, 3);                   // Calls subtract(5, 3)
    }else{
        printf("Invalid operation\n");
    }

    op = get_operation('*');        // op = multiply
    if(op != NULL) {
        op(5, 3);                   // Calls multiply(5, 3)
    }else{
        printf("Invalid operation\n");
    }

    return 0;
}

void add(int a, int b) {
    printf("Addition: %d\n", a + b);
}

void subtract(int a, int b) {
    printf("Subtraction: %d\n", a - b);
}

void multiply(int a, int b) {
    printf("Multiplication: %d\n", a * b);
}