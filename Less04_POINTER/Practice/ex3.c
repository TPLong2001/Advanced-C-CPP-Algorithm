#include <stdio.h>

int main() {
    // Void pointer example
    int a = 10;
    void *void_ptr = &a;
    printf("Địa chỉ: %p, giá trị int: %d\n", void_ptr, *(int *)void_ptr);
    
    // Void pointer example with float
    float f = 5.5;
    void_ptr = &f;
    printf("Địa chỉ: %p, giá trị float: %.2f\n",  void_ptr, *(float *)void_ptr);

    // Void pointer example with char
    char ch = 'A';
    void_ptr = &ch;
    printf("Địa chỉ: %p, giá trị char: %c\n", void_ptr, *(char *)void_ptr);
    
    // NULL pointer example
    int *null_ptr = NULL;
    if (null_ptr == NULL) {
        printf("The pointer is NULL\n");
    }
    
    // Constant pointer example
    int c1 = 40;
    int e = 50;
    int *const const_ptr = &c1;
    printf("Value of c1 using constant pointer: %d\n", *const_ptr);
    // const_ptr = &e; // This will cause a compilation error because const_ptr is a constant pointer

    // Pointer to constant example
    const int c2 = 60;
    const int *ptr_to_const = &c2;
    printf("Value of c2 using pointer to constant: %d\n", *ptr_to_const);
    // *ptr_to_const = 70; // This will cause a compilation error because ptr_to_const points to a constant

    // Constant pointer to constant example
    const int c3 = 80;
    const int *const const_ptr_to_const = &c3;
    printf("Value of c3 using constant pointer to constant: %d\n", *const_ptr_to_const);
    // const_ptr_to_const = &e; // This will cause a compilation error because const_ptr_to_const is a constant pointer
    // *const_ptr_to_const = 90; // This will cause a compilation error because const_ptr_to_const points to a constant

    // Pointer to pointer (double pointer) example
    int b = 20;
    int *ptr1 = &b;
    int **ptr2 = &ptr1;
    printf("Value of b using double pointer: %d\n", **ptr2);

    // Pointer to pointer to pointer (triple pointer) example
    int c = 30;
    int *ptr3 = &c;
    int **ptr4 = &ptr3;
    int ***ptr5 = &ptr4;
    printf("Value of c using triple pointer: %d\n", ***ptr5);

    return 0;
}

// Tiep theo - ex4: func poiter