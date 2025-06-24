#include <stdio.h>

struct {
    unsigned int age : 3;
    unsigned int grade : 4;
    unsigned int id : 5;
} Student;

int main() {
    Student.age = 4;
    Student.grade = 10;
    Student.id = 15;

    printf("Sizeof(Student) : %lu\n", sizeof(Student));

    printf("Student.age : %d\n", Student.age);
    printf("Student.grade : %d\n", Student.grade);
    printf("Student.id : %d\n", Student.id);

    return 0;
}