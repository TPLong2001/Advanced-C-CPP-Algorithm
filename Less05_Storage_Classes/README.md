
# Bài 5: STORAGE CLASSES

## Cấu trúc file trong C 

Trong lập trình C, tổ chức file hợp lý giúp mã nguồn dễ quản lý, bảo trì và mở rộng.  
Cấu trúc phổ biến thường bao gồm __file source (.c), file header (.h)__, và đôi khi có thêm file __makefile__ hoặc thư mục phụ.  

__File .h - Header File (Tệp tiêu đề):__
* Là file chứa __khai báo hàm, biến, macro__ giúp các file .c khác có thể sử dụng mà không cần định nghĩa lại.
* Thường được gọi là "header file" (tệp tiêu đề).
* Sử dụng ```#include``` để nhúng vào file .c.

__File .c - Source File (Tệp mã nguồn):__
* Là file chứa __định nghĩa của các hàm, biến, và logic chương trình__.
* Được biên dịch thành mã máy để tạo file thực thi.
* Thường được gọi là "source file" (tệp mã nguồn C).


## Extern

__Khái niệm Extern:__ dùng để khai báo __một biến toàn cục__ hoặc __1 hàm__ nào đó đã được định nghĩa ở phạm vi bên ngoài file đó. (chỉ khai báo chứ không định nghĩa giá trị).  

Điều này giúp chương trình hiểu rằng biến hoặc hàm đã được định nghĩa và sẽ được sử dụng từ một vị trí khác, giúp quản lý sự liên kết giữa các phần khác nhau của chương trình hoặc giữa các file nguồn.

__Ví dụ:__ 
* __main.c__
```c
#include <stdio.h>
#include "file.h"

int main() {
    display();  // sử dụng hàm display từ file.c
    return 0;
}

```
* __file.h__
```c
#ifndef FILE_H
#define FILE_H

extern int var_global; // Khai báo biến var_global định nghĩa ở file.c
extern void display(); // Khai báo hàm display định nghĩa ở file.c

#endif // FILE_H
```
* __file.c__
```c
#include<stdio.h>

int var_global = 50; //0x01

void display(){
    printf("var_global = %d\n", var_global);
}
```
__Kết quả:__
```
var_global = 50
```

📌 ____Chú ý:____  

✅ Khai báo __(extern)__ trong file __(.h)__. 

🚀 Sự khác biệt giữa __có extern__ và __không có extern__ khi khai báo hàm trong file __(.h)__:  
⚡ Trong C, hàm mặc định đã có "external linkage", nghĩa là nó có thể được sử dụng ở các file .c khác mà không cần từ khóa extern. Tuy nhiên, vẫn có một số trường hợp extern hữu ích. Vì vậy hàm __có extern__ và __không có extern__ thì sẽ tương tự nhau trong C.

## Static
### Static Local Variable
__Static local variables (biến cục bộ):__  
* Giữ giá trị của biến qua các lần gọi hàm.  
* Giữ phạm vi của biến chỉ trong hàm đó.
* Khởi tạo duy nhất 1 lần, lưu trữ trong vùng nhớ static,globle => tồn tại trong suốt vòng đời của chương trình.

__Ví dụ:__
```c
#include <stdio.h>

int *ptr = NULL;

void increment() {
    static int count = 0; // static variable
    ptr = &count;
    count++;
    printf("Count: %d\n", count);
}

int main() {
    increment();
    increment();
    increment();

    *ptr = 99;
    increment();
    return 0;
}
```
__Kết quả:__
```
Count: 1
Count: 2
Count: 3
Count: 100
```

### Static Globle Variable, Static Function
__Static global variables, Static Function (biến, hàm toàn cục):__  
* Giới hạn phạm vi biến toàn cục chỉ trong file .c chứa nó.
* Ngăn file bên ngoài sử dụng ```extern``` truy xuất.  

=> __Ứng dụng:__ dùng để thiết kế các file thư viện.

__Ví dụ:__
```c
static int num;
static void count(){
  int a = 0;
  printf("a = %d\n",a);
  a++;
}
```


📌 ____Chú ý:____  

✅ Sử dụng ```static``` trong file __(.c)__. Không khai báo lại trong file __(.h)__.  
❌ Nếu dùng ```static``` trong file __(.h)__. file __(.c)__```include``` file __(.h)__ sẽ không thể dùng được vì nó chỉ được định nghĩa trong file __(.c)__.

## Volatile
```volatile``` sử dụng để báo hiệu cho trình biên dịch rằng __giá trị biến có thể thay đổi ngẫu nhiên__, ngoài sự kiểm soát của chương trình.  

Việc này __ngăn chặn trình biên dịch tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó__, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.  

Điều này thường gặp khi làm việc với __biến phần cứng (hardware registers), bộ nhớ dùng chung (shared memory), hoặc biến trong ISR (Interrupt Service Routine).__

__Cú pháp khai báo:__
```c
volatile int x;
volatile uint8_t status;

```

## Register

Từ khóa ```register``` trong C gợi ý trình biên dịch __lưu trữ biến vào thanh ghi CPU__ thay vì RAM để tăng tốc độ truy xuất.  

Tuy nhiên, hầu hết các trình biên dịch hiện đại tự tối ưu hóa, nên register ít được sử dụng ngày nay.

__Ví dụ:__
```c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    // Without register
    int i, sum = 0;
    start = clock();
    for (i = 0; i < 100000000; i++) {
        sum += i;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken without register: %f seconds\n", cpu_time_used);

    // With register
    register int j, reg_sum = 0;
    start = clock();
    for (j = 0; j < 100000000; j++) {
        reg_sum += j;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken with register: %f seconds\n", cpu_time_used);

    return 0;
}

```

__Kết quả:__
```c
Time taken without register: 0.216000 seconds
Time taken with register: 0.034000 seconds
```