#include <stdio.h>

union Data {
    char s;
    int i;
    int arr[5];
};

int main() {
    union Data data;

    data.s = 10;
    printf("data.s : %d\n", data.s);


    data.i = 1000;
    printf("data.i : %d\n", data.i);

    // Assigning values to the array
    int tempArr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        data.arr[i] = tempArr[i];
    }
    printf("data.arr : ");
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", data.arr[i]);
    }
    printf("\n");

    printf("data.s : %d\n", data.s);
    printf("data.i : %d\n", data.i);

    return 0;
}