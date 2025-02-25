
# Bài 1 Macro - Compiler

## Compiler

Compiler hay còn được gọi là trình biên dịch. Nhiệm vụ của nó là biến đổi các ngôn ngữ lập trình về ngôn ngữ mà máy tính có thẻ hiểu được, đó là mã nhị phân với 0 và 1. 
 
Vì bản chất máy tính chỉ là 1 loại "máy" lên nó chỉ có thể hiểu được 0 và 1 tương ứng bật và tắt và nếu ta làm việc với toàn 0 và 1 thì quả thật quá bất tiện chính vì vậy mà nhiều ngôn ngữ bậc cao đã ra đời như C/C++, ... và phải cần 1 thứ gì đó để biến đổi các ngôn ngữ lập trình bậc cao đó về dạng mà máy tính có thể hiểu được là mã nhị phân gồm 0 với 1. Vì vậy Compiler ra đời.
  
**Để cụ thể hơn mình sẽ chỉ tập trung vào compiler trong C/C++ hay chính là quá trình biên dịch 1 chương trình C/C++:**
  
__Quá trình này sẽ được chia làm 4 giai đoạn chính:__

* Giai đoạn tiền xử lý (Pre-Processer)
* Giai đoạn dịch ngôn ngữ bậc cao sang Assembly (Compiler)
* Giai đoạn dịch Assembly sang ngôn ngữ máy (Assembler)
* Giai đoạn liên kết (Linker)

![Quá trình biên dịch 1 chương trình](img/GCC_CompilationProcess.png)

__Cách thức hoạt động từng quá trình:__

**- Pre-Processer:**  
Quá trình biển đổi từ file các file trong chương trình (.h .c) thành file (.i)  
Với cú pháp trong terminal tại đúng vị trí cảu folfer chương trình như sau:
```cmd
gcc -E main.c -o main.i
// Vì file của mình là ex1 lên mình chạy theo dòng bên dưới
gcc -E ex1.c -o ex1.i
```
Sau đó kiểm tra file .i chúng ta sẽ thấy được giai đoạn này sẽ xử lý các chỉ thị tiền xử lý:  
Ví dụ:  
```c
#include <stdio.h>
#include "test.c"

#define PI 3.14

int main() {
    printf("Hello, World!\n");
    displayMessage();
    printf("Value of PI: %f\n", PI);
    return 0;
}
```
các chỉ thị tiền xử lý như:  
#include <stdio.h> sẽ được thay thế bằng file thư viện stdio.h vào vị trí đó trong file.  
   
#define PI 3.14 - trong chương trình tất cả biến "PI" sẽ được thay thế hoàn toàn bằng "3.14" trực tiếp vào file.

Tiếp nữa là xóa bỏ toàn bộ chú thích của chương trình.  

**- Compiler:**  
Quá trình biển đổi từ file (.i) thành file (.s)  
Giai đoạn này ngôn ngữ sẽ được chuyển đổi toàn bộ về ngôn ngữ Assembly là ngôn ngữ bậc thấp gần với mã máy nhất.  
Cú pháp:  
```cmd
gcc -S ex1.c -o ex1.s
```
**- Assembler:**  
Quá trình biển đổi từ file (.s) thành file (.o)  
Giai đoạn này ngôn ngữ sẽ được chuyển đổi toàn bộ về ngôn ngữ máy dạng nhị phân.
Cú pháp:  
```cmd
gcc -c ex1.c -o ex1.o
```
**- Linker:**  
Quá trình này sẽ liên kết tất cả các file (.o) lại với nhau thành 1 file thực thi duy nhất (.exe)   
Cú pháp:  
```cmd
gcc ex1.c -o ex1
```

## Macro  

Macro là chỉ những thông tin được xử lý trong quá trình Tiền xử lý (Pre-Processer).  thường được đánh dấu bằng ký hiệu "#".

**Các nhóm chính của Macro như sau:**  

**- #include**  
Dùng để chèn nội dung của một file vào mã nguồn chương trình đó như đã nói ở trên.

**- #define, #undef**  
Dùng để định nghĩa/ hủy định nghĩa 1 hoặc 1 tập hợp các hướng dẫn tiền xử lý nào đó, nó sẽ thay thế chuỗi mã nguồn bằng 1 chuỗi mã nguồn đã được định nghĩa trước khi chương trình biên dịch.

**- #if, #elif, #else, #ifdef, #ifndef**  
Dùng khi ta muốn sử dụng các điều kiện trong tiền xử lý. Nếu #if đúng thì các dòng mã nguồn phía sau sẽ được biên dịch, nếu sai nó sẽ bị xóa đến khi gặp #endif. Tương tự ngược lại với #elif.

**- Các toán tử Macro**  
__Toán tử nối chuỗi: ##__  
```c
#define TEST(a, b) a ## b

int main() {
    int xy = 10;
    printf("%d", TEST(x, y));  // Kết quả là 10, vì TEST(x, y) trở thành "xy"
    return 0;
}

```
__Toán tử chuẩn hóa văn bản thành chuỗi: #__  
```c
#include <stdio.h>

#define STRINGIZE(x) #x
#define DATA 40

int main() {

    // Sử dụng toán tử #
    printf("The value is: %s\n", STRINGIZE(DATA));

    return 0;
}
```
__Variadic:__   
+ Biểu thị các đối số chuyền vào không xác định: ...
+ Thay thế thành danh sách đối số chuyền vào: __VA_ARGS__  
```c
#include <stdio.h>

#define PRINT(fmt, ...) printf(fmt, __VA_ARGS__)

int main() {
    PRINT("Số nguyên: %d\n", 10);         // Chỉ có một đối số
    PRINT("Hai số: %d và %d\n", 5, 8);    // Hai đối số
    PRINT("Dấu nháy: \"%s\"\n", "Hello"); // Một chuỗi
    return 0;
}

```