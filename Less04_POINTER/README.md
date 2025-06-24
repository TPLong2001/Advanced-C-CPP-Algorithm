
# Bài 4: POINTER

## Kích thước con trỏ và cú pháp

__Kích thước con trỏ__ phụ thuộc vào __Kiến trúc của máy tính__ và trình biên dịch thực thi.

* __Kiến trúc x86__, con trỏ sẽ có kích thước __32-bit (4 bytes)__
* __Kiến trúc x64__, con trỏ sẽ có kích thước __64-bit (8 bytes)__

Ta có thể kiểm tra kích thước của con trỏ bằng ```sizeof()```
```c
#include <stdio.h>

int main() {
    printf("Size of char pointer: %zu bytes\n", sizeof(char *));
    printf("Size of int pointer: %zu bytes\n", sizeof(int *));
    printf("Size of float pointer: %zu bytes\n", sizeof(float *));
    printf("Size of double pointer: %zu bytes\n", sizeof(double *));
    printf("Size of void pointer: %zu bytes\n", sizeof(void *));
    printf("Size of long pointer: %zu bytes\n", sizeof(long *));
    printf("Size of short pointer: %zu bytes\n", sizeof(short *));
    return 0;
}
```
Với hệ thống __64-bit__ kết quả thu được là: ```8 bytes```
```c
Size of char pointer: 8 bytes
Size of int pointer: 8 bytes
Size of float pointer: 8 bytes
Size of double pointer: 8 bytes
Size of void pointer: 8 bytes
Size of long pointer: 8 bytes
Size of short pointer: 8 bytes
```
Như vậy, __kích thước của con trỏ__ không phụ thuộc vào kiểu dữ liệu mà nó trỏ đến (int, char, float, v.v.), mà chỉ phụ thuộc vào __kiến trúc của hệ thống__.

***
#
  

  
____Cú pháp khai báo con trỏ____:

 ```<kiểu dữ liệu> *<tên con trỏ>;```

__Ví dụ:__
```c
int *p;     // Con trỏ trỏ đến một biến kiểu int
char *c;    // Con trỏ trỏ đến một biến kiểu char
float *f;   // Con trỏ trỏ đến một biến kiểu float
double *d;  // Con trỏ trỏ đến một biến kiểu double
```
Kiểu dữ liệu của con trỏ sẽ phụ thuộc vào kiểu dữ liệu của biến mà con trỏ trỏ tới.  

Khi __truy cập giá trị bằng con trỏ__, kiểu dữ liệu con trỏ sẽ cho phép bạn __truy cập giá trị__ đúng với __kích thước của kiểu dữ liệu đó__.  

__Ví dụ__:

```c
#include <stdio.h>
#include <stdint.h>

int main() {
    int x = 500;  //0b 00000001 11101000
    int *p = &x;
    uint8_t *c = (uint8_t*)p;       // con trỏ kiểu uint8_t trỏ tới địa chỉ của biến x
    uint8_t *d = (uint8_t*)p + 1;   // con trỏ kiểu uint8_t trỏ tới địa chỉ của biến x + 1 byte
    uint16_t *e = (uint16_t*)p;     // con trỏ kiểu uint16_t trỏ tới địa chỉ của biến x

    printf("Address of x: %p\n", p);
    printf("Value of x: %d\n", *p);
    printf("Value of x 1byte_Low: %d\n", *c); // 0b 11101000 - Lấy 1 byte đầu tiên của biến x
    printf("Value of x 1byte_High: %d\n", *d); // 0b 00000001 - Lấy 1 byte thứ 2 của biến x
    printf("Value of x 2byte: %d\n", *e);      // 0b 00000001 11101000 - Lấy 2 byte của biến x

    return 0;
}
```

__Kết quả:__
```
Address of x: 000000F126DFF6FC
Value of x: 500
Value of x  1byte_Low: 244
Value of x 1byte_High: 1
Value of x 2byte: 500
```
---
## Truyền con trỏ vào hàm

Khi truyền tham số vào hàm bằng __con trỏ__ => thay đổi giá trị của __biến thực sự__.  

Khi truyền tham số vào hàm bằng __giá trị__ => thay đổi giá trị của __biến tạm__, khi thoát khỏi hàm giá trị tạm sẽ bị xóa => giá trị truyền vào ban đầu __không thay đổi__.

__Ví dụ:__
```c
#include <stdio.h>

void swap1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap1(x, y);
    printf("After swap1: x = %d, y = %d\n", x, y);
    swap2(&x, &y);
    printf("After swap2: x = %d, y = %d\n", x, y);
    return 0;
}
```
__Kết quả:__
```
Before swap: x = 10, y = 20
After swap1: x = 10, y = 20
After swap2: x = 20, y = 10
```

Việc truyền tham số vào hàm bằng __con trỏ__ còn tránh tạo bản sao biến, tiết kiệm bộ nhớ hơn.


---

## Các kiểu con trỏ (Type pointer)

__Void Pointer:__

```void *``` (con trỏ kiểu void) là một __con trỏ không có kiểu dữ liệu__ cụ thể. Nó có thể trỏ đến bất kỳ kiểu dữ liệu nào (int, float, char, struct, v.v.).  

__Nhưng:__
 * Không thể __dereference (*ptr) trực tiếp__, phải __ép kiểu__ về kiểu phù hợp trước.
 * Không thể thực hiện các phép toán số học __(ptr++, ptr--)__, vì không biết kích thước dữ liệu.

Cú pháp: ```void *ptr;```

__Ví dụ:__
```c
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
    return 0;
}

```
__Kết quả:__
```
Địa chỉ: 000000CF395FFCBC, giá trị int: 10
Địa chỉ: 000000CF395FFCB8, giá trị float: 5.50
Địa chỉ: 000000CF395FFCB7, giá trị char: A
```

--------
#
__Null pointer:__

__Null Pointer__ là một con trỏ không trỏ đến bất kỳ địa chỉ hợp lệ nào.  

Nó thường được sử dụng để chỉ ra rằng con trỏ chưa được khởi tạo hoặc không chứa dữ liệu hợp lệ.

__Ví dụ:__
```c
#include <stdio.h>

int main() {
// NULL pointer example
    int *null_ptr = NULL;
    if (null_ptr == NULL) {
        printf("The pointer is NULL\n");
    }
    return 0;
}
```
__Kết quả:__
```
The pointer is NULL
```

---
#
__Con trỏ hằng, hằng con trỏ, hằng con trỏ hằng:__

Từ khóa ```const``` có thể được dùng với con trỏ để tạo 3 kiểu biến sau:
 
| Kiểu  | Cách khai báo      | Ý nghĩa       |
|--------------|------------|------------|
| __Con trỏ hằng__          | ```const int *ptr;```         | Giá trị mà con trỏ trỏ đến không thể thay đổi, nhưng con trỏ có thể trỏ đến địa chỉ khác. |
| __Hằng con trỏ__          | ```int *const ptr;```         | Con trỏ luôn trỏ đến một địa chỉ cố định, nhưng giá trị tại địa chỉ đó có thể thay đổi. |
| __Hằng con trỏ hằng__     | ```const int *const ptr;```   | Cả giá trị và địa chỉ mà con trỏ trỏ đến đều không thể thay đổi. |
  
__Ví dụ:__
```c
#include <stdio.h>

int main() {
    // Ví dụ về hằng con trỏ
    int c1 = 40;
    int e = 50;
    int *const const_ptr = &c1;
    printf("Giá trị của c1 sử dụng hằng con trỏ: %d\n", *const_ptr);
    // const_ptr = &e; // Lỗi biên dịch vì const_ptr là một hằng con trỏ nên không thể thay đổi địa chỉ nó trỏ đến

    // Ví dụ về con trỏ trỏ đến hằng
    const int c2 = 60;
    const int *ptr_to_const = &c2;
    printf("Giá trị của c2 sử dụng con trỏ trỏ đến hằng: %d\n", *ptr_to_const);
    // *ptr_to_const = 70; // Lỗi biên dịch vì ptr_to_const trỏ đến một hằng, không thể thay đổi giá trị

    // Ví dụ về hằng con trỏ trỏ đến hằng
    const int c3 = 80;
    const int *const const_ptr_to_const = &c3;
    printf("Giá trị của c3 sử dụng hằng con trỏ trỏ đến hằng: %d\n", *const_ptr_to_const);
    // const_ptr_to_const = &e; // Lỗi biên dịch vì const_ptr_to_const là một hằng con trỏ, không thể thay đổi địa chỉ
    // *const_ptr_to_const = 90; // Lỗi biên dịch vì const_ptr_to_const trỏ đến một hằng, không thể thay đổi giá trị
    return 0;
}

```
__Kết quả:__
```c
Giá trị của c1 sử dụng hằng con trỏ: 40  
Giá trị của c2 sử dụng con trỏ trỏ đến hằng: 60  
Giá trị của c3 sử dụng hằng con trỏ trỏ đến hằng: 80  

```

-------

## Function Pointer

__Function Pointer (con trỏ hàm)__ là một con trỏ trỏ đến địa chỉ của một hàm. Nó cho phép gọi hàm một cách linh hoạt, đặc biệt hữu ích khi làm việc với __callback, xử lý sự kiện.__

__Cú pháp khai báo:__  
```return_type (*pointer_name)(parameter_list);```

__Ứng dụng:__  
* __Function Pointer__ có thể sử dụng làm tham số truyền vào hàm (Callback).  
* __Mảng Function Pointer__, dùng mảng con trỏ hàm để lưu 1 loạt các hàm.  
* __Function Pointer__ trả về Con trỏ Hàm.

__Ví dụ:__

```c
#include <stdio.h>

// Khai báo các hàm
void add(int a, int b);
void subtract(int a, int b);
void multiply(int a, int b);

// Định nghĩa kiểu con trỏ hàm
typedef void (*operation)(int, int);

// Hàm sử dụng con trỏ hàm làm tham số (callback function)
void calculate(operation op, int a, int b) {
    op(a, b);
}

// Hàm trả về con trỏ hàm dựa vào phép toán được chọn
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
    // Sử dụng con trỏ hàm riêng lẻ
    printf("Sử dụng con trỏ hàm\n");
    operation op1 = add;
    operation op2 = subtract;
    operation op3 = multiply;

    op1(5, 3); // Gọi hàm add(5, 3)
    op2(5, 3); // Gọi hàm subtract(5, 3)
    op3(5, 3); // Gọi hàm multiply(5, 3)


    // Mảng con trỏ hàm
    printf("\nMảng con trỏ hàm\n");
    operation operations[3] = {add, subtract, multiply};

    for (int i = 0; i < 3; i++) {
        operations[i](5, 3);
    }


    // Sử dụng con trỏ hàm làm tham số truyền vào hàm
    printf("\nSử dụng con trỏ hàm làm tham số\n");
    calculate(add, 5, 3);
    calculate(subtract, 5, 3);
    calculate(multiply, 5, 3);


    // Sử dụng hàm trả về con trỏ hàm
    printf("\nSử dụng hàm trả về con trỏ hàm\n");
    operation op;

    op = get_operation('+');    // Lấy con trỏ hàm add
    if (op != NULL) {
        op(5, 3);               // Gọi hàm add(5, 3)
    } else {
        printf("Phép toán không hợp lệ\n");
    }

    op = get_operation('-');    // Lấy con trỏ hàm subtract
    if (op != NULL) {
        op(5, 3);               // Gọi hàm subtract(5, 3)
    } else {
        printf("Phép toán không hợp lệ\n");
    }

    op = get_operation('*');    // Lấy con trỏ hàm multiply
    if (op != NULL) {
        op(5, 3);               // Gọi hàm multiply(5, 3)
    } else {
        printf("Phép toán không hợp lệ\n");
    }

    return 0;
}

// Định nghĩa các hàm thực hiện phép toán
void add(int a, int b) {
    printf("Phép cộng: %d\n", a + b);
}

void subtract(int a, int b) {
    printf("Phép trừ: %d\n", a - b);
}

void multiply(int a, int b) {
    printf("Phép nhân: %d\n", a * b);
}
```
__Kết quả:__
```c
Sử dụng con trỏ hàm
Phép cộng: 8
Phép trừ: 2
Phép nhân: 15

Mảng con trỏ hàm
Phép cộng: 8
Phép trừ: 2
Phép nhân: 15

Sử dụng con trỏ hàm làm tham số
Phép cộng: 8
Phép trừ: 2
Phép nhân: 15

Sử dụng hàm trả về con trỏ hàm
Phép cộng: 8
Phép trừ: 2
Phép nhân: 15
```

