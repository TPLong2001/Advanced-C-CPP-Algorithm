#include <stdio.h>
#include <string.h>

// Define a struct to hold information about a person
typedef struct Person {
    char name[50];
    int age;
    float height;
}Person;

int main() {
    // Declare and initialize a variable of type struct Person
    Person person1 = {"John Doe", 30, 5.9};

    // Print the values of the fields of person1
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Height: %.1f\n", person1.height);

    return 0;
}