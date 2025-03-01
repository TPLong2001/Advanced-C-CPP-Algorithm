#include <stdio.h>

int main() {
    int num = 0;

    printf("Enter a number (1 to 5): ");
    scanf("%d", &num);

    if (num < 1 || num > 5) {
        goto error;
    }

    printf("You entered: %d\n", num);
    return 0;

error:
    printf("Invalid number! Please enter a number between 1 and 5.\n");
    return 1;
}