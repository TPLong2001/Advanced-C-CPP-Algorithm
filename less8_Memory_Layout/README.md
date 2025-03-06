---

# BÀI 8: MEMORY LAYOUT

## Tổng quan

Chương trình `main.exe` ( trên window), `main.hex` ( nạp vào vi điều khiển) được lưu ở bộ nhớ __SSD__ hoặc __FLASH.__ Khi nhấn run chương trình trên window (cấp nguồn cho vi điều khiển) thì những chương trình này sẽ được __copy vào bộ nhớ RAM__ để thực thi.

Các vùng nhớ sẽ được phân bổ như sau:

| __Vùng nhớ__  | __Bao gồm__      | __Đặc điểm__       |
|--------------|------------|------------|
| __Text__ | Code (machine code)  | Thường chỉ đọc và thực thi |
| __Data__ | Biến toàn cục/static khởi tạo (≠0) | Đọc/ghi, lưu trữ đến khi kết thúc chương trình |
| __BSS__ | Biến toàn cục/static khởi tạo = 0 |  Đọc/ghi, lưu trữ đến khi kết thúc chương trình |
| __Heap__ | Cấp phát động | Đọc/ghi, người dùng tự cấp phát và quản lý |
| __Stack__ | Biến cục bộ, tham số, return address | Đọc/ghi, hệ thống cấp phát và quản lý |

## Text Segment

Đây là vùng địa chỉ thấp nhất lưu trữ mã lệnh của chương trình.

* Chứa mã lệnh (instruction) của chương trình.
* Lưu trữ các biến const và dữ liệu trong con trỏ chuỗi khai báo như sau: char *ptr = "abc";
* Vùng này có thuộc tính read-only (chỉ đọc) và thực thi để bảo vệ mã nguồn không bị ghi đè hoặc sửa đổi trong quá trình chạy.


## .rdata (Read-Only Data)

* Là vùng dữ liệu chỉ đọc, thường chứa các dữ liệu __hằng số toàn cục__ hoặc __các chuỗi bất biến (string literals)__, không thay đổi trong suốt quá trình chạy chương trình.
* `.rdata` thường nằm cạnh vùng `.text` (chứa code) trong file thực thi.

__Ví dụ:__

```c
#include <stdio.h>

const int MAX = 100;            // Read-Only Data (hoặc có thể chung vùng Text)

const char message[] = "Hi";    // Read-Only Data (hoặc có thể chung vùng Text)

char *str = "Hello, World!";    // "Hello, World!" (string literals)

void hello() {
    printf("%s\n", str);
}

int main() {
    hello();
    str[0] = 'B';               // error -> dừng ctrinh
    hello();
    return 0;
}

```

__Kết quả:__
```c
Hello, World!
```

## Data Segment
__Data Segment__ là một vùng bộ nhớ của tiến trình được cấp phát khi chương trình thực thi gồm:

* Các biến toàn cục (`global`) và biến tĩnh (`static`) có __giá trị khởi tạo khác 0 hoặc khác NULL__.
* Vùng này có thể __đọc/ghi__ (read/write).
* Lưu trữ cố định trong suốt vòng đời chương trình.

__Ví dụ:__

```c
#include <stdio.h>

int global_init = 100;        // Data Segment (đã khởi tạo)
static int static_init = 200; // Data Segment (tĩnh và khởi tạo)
const char message[] = "Hi";  // Read-Only Data (hoặc có thể chung vùng Text)

int global_uninit;            // BSS Segment (chưa khởi tạo)
static int static_uninit;     // BSS Segment (tĩnh chưa khởi tạo)

int main() {
    printf("%d %d %s\n", global_init, static_init, message);
    return 0;
}

```

__Kết quả:__
```c
100 200 Hi
```

## BSS Segment

BSS Segment (Block Started by Symbol) là vùng bộ nhớ của tiến trình được cấp phát khi chương trình thực thi gồm:

* Các biến toàn cục (`global`) và biến tĩnh (`static`) __chưa được khởi tạo giá trị cụ thể__ khi biên dịch (hoặc __khởi tạo bằng giá trị 0__).
* Vùng này có thể __đọc/ghi__ (read/write).
* Lưu trữ cố định trong suốt vòng đời chương trình.

__Ví dụ:__

```c
#include <stdio.h>

// Uninitialized global variable
int global_var;             // BSS Segment (toàn cục chưa khởi tạo)  

 // Uninitialized static variable
static int static_var;      // BSS Segment (static chưa khởi tạo)

int main() {
   
    printf("Value of uninitialized global variable: %d\n", global_var);
    printf("Value of uninitialized static variable: %d\n", static_var);

    return 0;
}

```

__Kết quả:__
```c
Value of uninitialized global variable: 0
Value of uninitialized static variable: 0
```

## Stack Segment

Vùng Stack hoạt động theo cơ chế LIFO (Last In, First Out), nghĩa là dữ liệu được đẩy vào sau cùng sẽ được lấy ra trước.

Stack Segment là vùng bộ nhớ dùng để lưu trữ:

* Biến cục bộ (local variables).
* Tham số (parameters) của hàm.
* Địa chỉ trả về khi gọi hàm.
* Thông tin phục vụ quá trình đệ quy, gọi hàm lồng nhau.

__Ví dụ:__

```c
#include <stdio.h>

void foo(int x) {
    int a = 10;         // Biến cục bộ → Stack
    int b = x + a;      // Biến cục bộ → Stack
    printf("%d\n", b);
}

void display(int x, const char *str) {
    const int local_const = 20;      // Biến hằng cục bộ → Stack

    int *ptr = &local_const;           // Con trỏ cục bộ → Stack (trỏ đến biến trong Stack)

    printf("x = %d\n", x);           // Tham số x → Stack
    printf("str = %s\n", str);       // Tham số str → Stack (trỏ đến vùng dữ liệu .rodata)
    printf("local_const = %d\n", local_const);
    *ptr = 10;
    printf("local_const = %d\n", local_const);
    printf("*ptr = %d\n", *ptr);     // Trỏ đến local_var
}

int main() {
    int number = 5;                  // Biến cục bộ → Stack
    foo(number);                     // Gọi hàm foo, đẩy num làm tham số vào Stack
    
    const char *message = "Hello";   // Con trỏ cục bộ → Stack (trỏ đến vùng .rodata)
    display(number, message);        // Truyền tham số vào Stack
    return 0;
}
```

__Kết quả:__
```c
15
x = 5
str = Hello
local_const = 20
local_const = 10
*ptr = 10
```

## Heap Segment

__Heap Segment__ là vùng bộ nhớ động (dynamic memory) dùng để cấp phát bộ nhớ khi chương trình đang chạy (runtime).  

Khác với Stack (cấp phát tự động), vùng Heap cho phép __cấp phát và giải phóng bộ nhớ bằng tay__ thông qua các hàm như: `malloc()`, `calloc(`), `realloc()`, `free()`.

### `malloc()`

Là hàm cấp phát bộ nhớ động với kích thước chỉ định, nhưng __không khởi tạo giá trị__ (giá trị rác).  
__Cú pháp__: 
```c
void *malloc(size_t size);
```

Hàm trả về con trỏ `void*` trỏ đến vùng đã được cấp phát và `size` là kích thước vùng nhớ được cấp phát.


__Ví dụ:__

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;                          // Con trỏ cục bộ (Stack)
    int n = 5;                         // Biến cục bộ (Stack)

    // Cấp phát động vùng nhớ cho 5 số nguyên trên vùng nhớ Heap
    ptr = (int *)malloc(n * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Thoát nếu cấp phát thất bại
    }
    // In giá trị
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    free(ptr); // Giải phóng vùng nhớ Heap
    return 0;
}

}
```

__Kết quả:__
```c
7209061 6881397 6619246 7209033 6619252 
```

### `calloc()`

Hàm tương tự như `malloc()` nhưng cấp phát bộ nhớ động và khởi tạo toàn bộ về 0.  

__Cú pháp__: 
```c
void *calloc(size_t num, size_t size);
```

Hàm trả về con trỏ `void*` trỏ đến vùng đã được cấp phát và `size` là kích thước phần tử cấp phát, num là số phần tử cần cấp phát.  

Vì nó sẽ khởi tạo luôn từng phần tử với giá trị bằng 0 lên nó cần phải biết rõ kích thước dữ liệu của từng phần tử là bao nhiêu và số lượng phần tử nữa => cần 2 tham số khác so với `malloc` chỉ cần số byte


__Ví dụ:__

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    ptr = (int *)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);  // Sẽ in ra toàn số 0
    }
    free(ptr);
    return 0;
}

```

__Kết quả:__
```c
0 0 0 0 0
```

### `realloc()`

Hàm dùng để __thay đổi kích thước của vùng nhớ__ đã cấp phát động (bằng malloc(), calloc(), hoặc realloc() trước đó).  

Giúp __mở rộng hoặc thu nhỏ__ vùng nhớ trên Heap mà không mất dữ liệu cũ (nếu mở rộng, phần dữ liệu mới không khởi tạo).

__Cú pháp__: 
```c
void *realloc(void *ptr, size_t new_size);
```

Hàm trả về con trỏ `void*` trỏ đến vùng đã được cấp phát và `size` là kích thước vùng nhớ sẽ thay đổi, `ptr` là con trỏ đang trỏ vào vùng nhớ cần thay đổi kích thước.

__Ví dụ:__

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    ptr = (int *)malloc(n * sizeof(int));
    if (ptr == NULL) {
        printf("Initial allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        ptr[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    // Mở rộng vùng nhớ lên 10 phần tử
    ptr = (int *)realloc(ptr, 10 * sizeof(int));
    if (ptr == NULL) {
        printf("Reallocation failed.\n");
        return 1;
    }

    for (int i = n; i < 10; i++) {
        ptr[i] = (i + 1) * 10;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", ptr[i]);
    }

    free(ptr);
    return 0;
}
```

__Kết quả:__
```c
1 2 3 4 5 
1 2 3 4 5 60 70 80 90 100
```

### MEMORY LEAK

__Lỗi rò rỉ bộ nhớ (Memory Leak)__ xảy ra khi bộ nhớ động được cấp phát (bằng malloc(), calloc(), realloc(),...) nhưng:

* Không được giải phóng bằng free().
* Không còn cách nào để truy xuất lại để giải phóng.  

Những vùng bộ nhớ này bị chiếm dụng vĩnh viễn trong suốt thời gian chương trình chạy, khiến tài nguyên bị lãng phí.

Nếu tình trạng này xảy ra liên tục, chương trình sẽ tiêu tốn hết bộ nhớ hệ thống và có thể bị treo hoặc bị crash.

__Nguyên nhân gây rò rỉ bộ nhớ:__
* __Bị mất địa chỉ bộ nhớ (Losing the address)__

Khi cấp phát bộ nhớ xong nhưng con trỏ trỏ đến vùng nhớ đó bị gán giá trị khác, làm mất địa chỉ của vùng nhớ, dẫn tới không thể giải phóng nữa.

```c
int *ptr = (int *)malloc(sizeof(int) * 10);
ptr = NULL;  // Mất địa chỉ vùng nhớ đã cấp phát
```

* __Không sử dụng free() để giải phóng__

Chương trình cấp phát xong nhưng quên hoặc không gọi free() để thu hồi lại vùng nhớ sau khi dùng.

* __Rò rỉ ẩn (Hidden leak):__

Khi con trỏ trỏ đến vùng nhớ động bị ghi đè bởi địa chỉ mới, trong khi vùng nhớ cũ không được free().

```c
int *ptr = (int *)malloc(100);
ptr = (int *)malloc(200);  // Rò rỉ vùng nhớ 100 byte ban đầu
free(ptr);  // Chỉ giải phóng vùng nhớ 200 byte mới
```