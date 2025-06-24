
# Bài 6: GOTO - SETJMP
 
## Goto
__"goto"__ là một từ khóa trong C, câu lệnh goto là một câu lệnh nhảy (jump) vô điều kiện.  

Khi sử dụng câu lệnh nó sẽ __nhảy đến một nhãn đã đặt__ trước đó.  

Việc nhảy vô điều kiện như vậy khiến ta rất dể dàng sử dụng để kiểm soát flow của chương trình, nhưng nếu lạm dụng nó có thể khiến cho chương trình trở lên khó đọc và bảo trì.

__Ứng dụng:__  
* Xử lý lỗi
* Thoát khỏi vòng lặp nhiều cấp độ

__Hạn chế:__
* Code khó đọc, khó bảo trì.
* Dễ gây lỗi và khó theo dõi flow.

__Ví dụ 1:__
```c
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
```

__Kết quả 1:__
```
Enter a number (1 to 5): 7
Invalid number! Please enter a number between 1 and 5.
```

__Ví dụ 2:__
```c
#include <stdio.h>

int main() {
    int i, j, k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (i == 2 && j == 3 && k == 1) {
                    goto end_loops;
                }
                printf("i = %d, j = %d, k = %d\n", i, j, k);
            }
        }
    }

end_loops:
    printf("Exited the loops at i = %d, j = %d, k = %d\n", i, j, k);

    return 0;
}

```

__Kết quả 2:__
```
i = 0, j = 0, k = 0
i = 0, j = 0, k = 1
i = 0, j = 0, k = 2
...................
i = 2, j = 2, k = 4
i = 2, j = 3, k = 0
Exited the loops at i = 2, j = 3, k = 1
```

## Setjmp 

```setjmp.h``` là 1 thư viện xử lý nhảy không tuần tự trong C.

Thư viện ```<setjmp.h>``` trong C cung cấp hai hàm quan trọng:

* __setjmp()__: Lưu trạng thái chương trình.  
* __longjmp()__: Nhảy về trạng thái đã lưu trước đó.  

Thư viện này được sử dụng để thoát khỏi một hàm đột ngột hoặc xử lý lỗi không đồng bộ.

```C
#include <setjmp.h>

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

```

__Cách hoạt động:__
* ```env```: Biến kiểu ```jmp_buf```, dùng để lưu trạng thái chương trình.
* Khi gọi ```setjmp(env) lần đầu```, nó lưu trạng thái và trả về __0__.
* Nếu sau đó gọi ```longjmp(env, val)```, ```setjmp(env)``` sẽ trả về __val__.

__Ví dụ:__
```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf buffer;

void second() {
    printf("second\n");
    longjmp(buffer, 1);
}

void first() {
    second();
    printf("first\n"); // This line will not be executed
}

int main() {
    if (setjmp(buffer) == 0) {
        first();
    } else {
        printf("main\n");
    }
    return 0;
}
}
```

__Kết quả:__
```
second
main
```

__Xử lý ngoại lệ:__

Ứng dụng để mô phỏng xử lý ngoại lệ theo cấu trúc TRY - CATCH - THROW.

__Ví dụ:__
```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf buffer;

void second() {
    printf("second\n");
    longjmp(buffer, 1);
}

void first() {
    second();
    printf("first\n"); // This line will not be executed
}

int main() {
    if (setjmp(buffer) == 0) {
        first();
    } else {
        printf("main\n");
    }
    return 0;
}
}
```

__Kết quả:__
```
In try block
In functionThatThrows with exception type 2
In catch block for exception 2
After try-catch block
```