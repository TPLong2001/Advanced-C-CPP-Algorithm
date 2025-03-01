
# Bài 7: STRUCT - UNION

## Struct 

__struct__ là một cấu trúc dữ liệu cho phép lập trình viên __tự định nghĩa một kiểu dữ liệu mới__ bằng cách __nhóm các biến có các kiểu dữ liệu khác lại với nhau__.  

__struct__ cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.

__Cú pháp khai báo:__

```c
struct StructName {
    data_type member1;
    data_type member2;
    ...
};
```

__Ví dụ:__

```c
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
```
__Kết quả:__
```c
Name: John Doe
Age: 30
Height: 5.9
```

📌 __Kích thước của struct phụ thuộc vào:__
* __Kích thước của từng thành viên.__
* __Yêu cầu căn chỉnh (Alignment Requirements).__
* __Padding (Lấp đầy bộ nhớ).__
* __Tổng kích thước của struct__ phải là bội số của __thành viên có yêu cầu căn chỉnh lớn nhất__.


🔹 Mỗi kiểu dữ liệu trong struct có __yêu cầu căn chỉnh (alignment requirement)__:

| Kiểu  | Kích thước      | Yêu cầu căn chỉnh      |
|--------------|------------|------------|
| ```char```    | 1 byte | Có thể nằm ở bất kỳ đâu. |
| ```short```   | 2 byte | Phải nằm ở địa chỉ chia hết cho 2. |
| ```int```     | 4 byte | Phải nằm ở địa chỉ chia hết cho 4. |
| ```float```   | 4 byte | Phải nằm ở địa chỉ chia hết cho 4. |
| ```double```  | 8 byte | Phải nằm ở địa chỉ chia hết cho 8. |
| ```long```    | 8 byte | Phải nằm ở địa chỉ chia hết cho 8. |

🔹 __Padding__ (đệm bộ nhớ) là __các byte trống__ được __chèn vào struct__ để đảm bảo mỗi thành viên trong struct được __đặt__ tại __địa chỉ căn chỉnh đúng__.

__Ví dụ:__
```c
#include <stdio.h>

struct Example {
    char a;        // 1 byte
    // Thêm 3 byte đệm để căn chỉnh `b` sao cho bắt đầu tại địa chỉ chia hết cho 4
    int b;         // 4 byte
    char c;        // 1 byte
    // Thêm 7 byte đệm để căn chỉnh `d` sao cho bắt đầu tại địa chỉ chia hết cho 8
    double d;      // 8 byte
    short e;       // 2 byte
    // Thêm 6 byte đệm để tổng kích thước của struct là bội số của phần tử có căn chỉnh lớn nhất (8 byte)
};

int main() {
    struct Example ex;
    printf("Kích thước của struct Example: %lu byte\n", sizeof(ex));
    return 0;
}

```

__Kết quả:__
```c
Kích thước của struct Example: 32 byte
```

__Bit-field__

__bit field__ (trường bit) là một thành phần đặc biệt của cấu trúc (struct) cho phép bạn __chỉ định số lượng bit cụ thể dùng để lưu trữ một biến số nguyên__.  

Thay vì sử dụng toàn bộ kích thước của một kiểu dữ liệu, bạn có thể “cắt nhỏ” bộ nhớ theo số bit cần thiết, giúp tiết kiệm không gian bộ nhớ và mô tả chính xác hơn ý nghĩa của dữ liệu (ví dụ: lưu trạng thái bật/tắt chỉ cần 1 bit).  

__Ví dụ:__
```c
#include <stdio.h>

struct {
    unsigned int age : 3;
    unsigned int grade : 4;
    unsigned int id : 5;
} Student;

int main(){
    Student.age = 4;
    Student.grade = 10;
    Student.id = 15;

    printf("Sizeof(Student) : %lu\n", sizeof(Student));

    printf("Student.age : %d\n", Student.age);
    printf("Student.grade : %d\n", Student.grade);
    printf("Student.id : %d\n", Student.id);

    return 0;
}

```

__Kết quả:__
```c
Sizeof(Student) : 4
Student.age : 4
Student.grade : 10
Student.id : 15
```

📌 __Lưu ý:__
* __Không thể lấy địa chỉ của bit field.__
* __Độ rộng bit-field phải nhỏ hơn hoặc bằng độ rộng bit của kiểu.__

## Union 

__union__ là một cấu trúc dữ liệu giúp lập trình viên kết hợp nhiều kiểu dữ liệu khác nhau vào cùng một vùng nhớ.  

Mục đích chính của union là tiết kiệm bộ nhớ bằng cách __chia sẻ cùng một vùng nhớ cho các thành viên của nó__.   

Điều này có nghĩa là, __trong một thời điểm, chỉ một thành viên của union có thể được sử dụng__. Điều này được ứng dụng nhằm tiết kiệm bộ nhớ.

__Cú pháp khai báo:__

```c
union StructName {
    data_type member1;
    data_type member2;
    ...
};
```
__Ví dụ:__
```c
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
}

```

__Kết quả:__
```c
data.s : 10
data.i : 1000
data.arr : 1 2 3 4 5
data.s : 1
data.i : 1
```
