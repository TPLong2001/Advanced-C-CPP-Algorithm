
# Bài 2 STDARG - ASSERT

## STDARG

Thư viện stdarg.h cung cấp các công cụ để làm việc với các hàm có số lượng đối số truyền vào không xác định. Thư viện này rất hữu ích khi bạn muốn định nghĩa các hàm có thể nhận số lượng đối số khác nhau mỗi lần gọi.  

__Ví dụ điển hình đó là các hàm ta hay sử dụng: printf() và scanf()__  

Trong thư viện gồm các hàm giúp ta xử lý phần đối số truyền vào không xác định:  
* **va_list**: Định nghĩa một kiểu dữ liệu để lưu trữ thông tin về danh sách các đối số không xác định.  
* **va_start**: Khởi tạo một biến va_list để trỏ đến danh sách các đối số.
* **va_arg**: Lấy giá trị của đối số tiếp theo trong danh sách theo kiểu dữ liệu xác định bằng tham số thứ 2.
* **va_end**: Giải phóng bộ nhớ mà va_list đã sử dụng.

### Ví dụ 1:
```c
#include <stdio.h>
#include <stdarg.h>

void test(int count, ...){
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        printf("value%d: %d\n", i + 1, va_arg(args, int));
    }   
    va_end(args);
}

int main(){
    test(4, 5, 7, 3, 4);
    return 0;
}
```
__Kết quả 1:__
```c
value1: 5
value2: 7
value3: 3
value4: 4
```
Từ __ví dụ 1__ ta thấy tham số đầu tiên nhập vào __int count__ sẽ là số phần tử nhập phía sau và sau đó danh sách phần tử phía sau phần tử đầu sẽ được trỏ vào bởi con trỏ __va_list args__. Ta sẽ dùng hàm __va_arg(args, int)__ để lấy lần lượt từng phần tử tiếp theo trong danh sách __args__ ra theo kiểu dữ liệu __int__ bằng vòng lặp __for__ với số lần lặp chính là phần tử __count__.

### Ví dụ 2:
```c
#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__, 'a')

int sum(int count, ...){
    va_list args;
    va_list args1;

    va_start(args, count);
    va_copy(args1, args);

    int sum = count;
    char *value;

    while ((value = va_arg(args1, char*)) != (char*)'a'){
        sum += va_arg(args, int);
    }   
    va_end(args);
    return sum;
}

int main(){
    printf("Sum: %d\n", tong(4, 5, 'b', 96, 97));
    // 97 = 'a' lên vẫn bị dừng ở  số 97 => sum = 4 + 5 + 98 + 96 = 203
    return 0;
}
```
__Kết quả 2:__
```c
Sum: 203
```
Với __Ví dụ 2__ ta sử dụng kết hợp __define__ và 1 điều kiện dừng để tạo lên 1 hàm có danh sách phần tử nhập vào bất kỳ mà không cần phải xác định số phần tử ở phần tử đầu tiên truyền vào, thay vào đó ta thêm 1 điều kiện dừng vào cuối danh sách bằng cách dùng __define__, điều kiện dừng nàu giúp hàm xác định được vị trí kết thúc của danh sách.  

Phần tử __VA_ARGS__ dùng để thay thế cho (...) chính là danh sách các đối số truyền vào vì vậy khi ta nhập danh sách đối số vào hàm __tong(...)__ nó sẽ tự chuyển đổi thành hàm __sum(...,'a')__ có giá trị __'a'__ ở cuối của danh sách. 

## ASSERT  

Thư viện __assert.h__ cung cấp một cơ chế để kiểm tra các điều kiện trong mã nguồn và báo lỗi __(dừng chương trình)__ nếu điều kiện không được thỏa mãn. Đây là công cụ hữu ích để kiểm tra giả định (assumptions) trong chương trình trong suốt quá trình phát triển và gỡ lỗi.

Thư viện cung cấp macro __assert__ để kiểm tra điều kiện trong hàm. Nếu điều kiện kiểm tra là sai, __assert__ sẽ in ra một thông báo lỗi và dừng chương trình, giúp phát hiện vấn đề trong quá trình phát triển và debug.

__Các lỗi chúng ta thường gặp:__
* Lỗi truy cập mảng không an toàn.
* Lỗi chia cho số 0.
* Chia số nguyên cho số nguyên, kết quả là số thực.

Ví dụ:
```c
#include <stdio.h>
#include<assert.h>

#define LOG(conddition, cmd)    assert(conddition && #cmd)

double divide(double a, double b)
{
    //assert(b != 0 && "Divide by zero");
    LOG(b != 0, Divide by zero);
    return a / b;
}

int main( int argc, char *argv[] )
{
    printf("Result: %f\n", divide(10, 0));
    return 0;
}
```
Kết quả:
```c
Assertion failed: b != 0 && "Divide by zero", file EX0.c, line 9
```


__Kết hợp với NDEBUG:__  
Nếu ta định biên dịch chương trình trong chế độ release (phiên bản đã tối ưu), có thể tắt __assert__ để tránh overhead không cần thiết.  
Để tắt __assert__, chỉ cần định nghĩa __NDEBUG__ trước khi biên dịch:
```c
#define NDEBUG
#include <assert.h>
```
Khi __NDEBUG__ được định nghĩa, tất cả các lời gọi __assert__ sẽ bị loại bỏ trong quá trình biên dịch và chương trình sẽ không kiểm tra điều kiện nữa.

 