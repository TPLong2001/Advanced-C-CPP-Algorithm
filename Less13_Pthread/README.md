
# Bài 13: Pthread

## 1. Tổng quan:

Khi 1 chương trình C thông thường thực hiện chạy các tác vụ 1 cách tuần tự từng task.

Mỗi task sẽ phải hoàn thành xong rồi mới tới các task tiếp theo.

__Câu hỏi đặt ra__ là nếu ta có __nhiều tác vụ__ và muốn chúng __cùng hoạt động song song__ thì sao?

=> Ta cần sử dụng các __cơ chế song song hóa (parallelism)__, ví dụ như:

+ __Đa luồng__ (multi-thread).
+ __Đa tiến trình__ (multimulti-process) với các task độc lập.
+ __Đa nhân__ (multi-corecore)
+ __Sử dụng OS__ lập lịch.

## 2. Multi-thread

__Thread (luồng)__: là đơn vị nhỏ nhất của CPU có thể được lập lịch và thực thi.

Một __Process__ (tiến trình) có thể chứa nhiều thread.

Các thread trong cùng một process __chia sẻ cùng vùng địa chỉ__ (code, data, heap), nhưng __mỗi thread__ có __stack và bộ đếm riêng__.

__MultiThread (đa luồng)__: llà kỹ thuật cho phép nhiều luồng thực thi đồng thời trong cùng một tiến trình.

## 3. Thư viện `pthread`:

`pthread` là __thư viện chuẩn POSIX__ để lập trình __đa luồng__ trong C/C++

Được dùng phổ biến trong Linux, Unix, và cả các hệ điều hành nhúng

__Cung cấp API để:__

- Tạo & kết thúc thread

- Truyền dữ liệu vào thread

- Đồng bộ: mutex, semaphore, condition...

__Để tạo mới 1 thread:__   
Sử dụng hàm pthread_create trong thư viện Pthread:
- Khởi chạy một thread.
- Chỉ định cho thread này thực thi một tác vụ cụ thể.

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
```
- `thread`: biến lưu ID của thread

- `attr`: thuộc tính thread (NULL nếu mặc định)

- `start_routine`: hàm sẽ được thread thực thi

- `arg`: tham số truyền vào hàm (có thể là struct, int, ...)

__Kết thúc và thu dọn thread:__  
Hàm `pthread_join(thread, NULL)`
- __Chờ thread kết thúc__ và __thu hồi tài nguyên__ ( không cần thì để là NULL như mình)

- Tránh __zombie thread__.

Hàm `pthread_detach(thread)`
- Không cần chờ join, thread sẽ __tự giải phóng__ khi kết thúc

- Dùng cho các thread chạy nền không cần lấy kết quả

## 4. Đồng bộ hóa trong đa luồng

__Điều kiện tranh chấp (Race Condition):__  
- Là hiện tượng 2 hoặc __nhiều thread cùng truy cập và ghi cùng một vùng dữ liệu__, gây ra kết quả sai lệch, tùy thuộc vào thứ tự thực thi.

=> Cần có 1 cơ chế để tránh race condition. Đó là cách sử dụng __`mutex`__

__Mutex (Multual Exclusion):__

- Là một cơ chế đảm bảo rằng __tại một thời điểm__, chỉ có duy nhất __một luồng__ (thread) __truy cập__ vào một vùng dữ liệu dùng chung.

- Nếu một thread đã __khóa mutex__, thì các thread khác __phải chờ__ cho đến khi mutex được __mở khóa__.

- Cách dùng:
```c
pthread_mutex_t lock;
int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
```

## 5. Demo

__Ví dụ:__
```c
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4 
#define NUM_INCREMENTS 30 

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    printf("--> Thread %d bắt đầu.\n", *(int*)arg);

    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        pthread_mutex_lock(&lock);
        counter++;
        printf("counter thread %d: %d\n", *(int*)arg, counter);
        pthread_mutex_unlock(&lock);
    }
    printf(" xx Thread %d kết thúc.\n", *(int*)arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int pthread_ids[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, increment, &pthread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Giá trị counter cuối cùng là: %d\n", counter);

    return 0;
}

```

__Kết quả:__
```c
--> Thread 2 bắt đầu.
--> Thread 3 bắt đầu.
--> Thread 1 bắt đầu.
--> Thread 4 bắt đầu.
counter thread 2: 1
counter thread 2: 2
counter thread 1: 3
counter thread 1: 4
counter thread 1: 5
counter thread 1: 6
counter thread 1: 7
counter thread 1: 8
counter thread 1: 9
counter thread 1: 10
counter thread 1: 11
counter thread 1: 12
counter thread 1: 13
counter thread 1: 14
counter thread 1: 15
counter thread 1: 16
counter thread 1: 17
counter thread 1: 18
counter thread 1: 19
counter thread 1: 20
counter thread 1: 21
counter thread 4: 22
counter thread 4: 23
counter thread 4: 24
counter thread 4: 25
counter thread 4: 26
counter thread 4: 27
counter thread 4: 28
counter thread 4: 29
counter thread 4: 30
counter thread 4: 31
counter thread 4: 32
counter thread 4: 33
counter thread 4: 34
counter thread 4: 35
counter thread 4: 36
counter thread 4: 37
counter thread 4: 38
counter thread 4: 39
counter thread 4: 40
counter thread 4: 41
counter thread 4: 42
counter thread 4: 43
counter thread 4: 44
counter thread 4: 45
counter thread 4: 46
counter thread 4: 47
counter thread 4: 48
counter thread 4: 49
counter thread 4: 50
counter thread 4: 51
 xx Thread 4 kết thúc.
counter thread 1: 52
counter thread 1: 53
counter thread 1: 54
counter thread 1: 55
counter thread 1: 56
counter thread 1: 57
counter thread 1: 58
counter thread 1: 59
counter thread 1: 60
counter thread 1: 61
counter thread 1: 62
 xx Thread 1 kết thúc.
counter thread 3: 63
counter thread 3: 64
counter thread 3: 65
counter thread 3: 66
counter thread 3: 67
counter thread 3: 68
counter thread 3: 69
counter thread 3: 70
counter thread 3: 71
counter thread 3: 72
counter thread 3: 73
counter thread 3: 74
counter thread 3: 75
counter thread 3: 76
counter thread 3: 77
counter thread 3: 78
counter thread 3: 79
counter thread 3: 80
counter thread 3: 81
counter thread 3: 82
counter thread 3: 83
counter thread 3: 84
counter thread 3: 85
counter thread 3: 86
counter thread 3: 87
counter thread 3: 88
counter thread 3: 89
counter thread 3: 90
counter thread 3: 91
counter thread 3: 92
 xx Thread 3 kết thúc.
counter thread 2: 93
counter thread 2: 94
counter thread 2: 95
counter thread 2: 96
counter thread 2: 97
counter thread 2: 98
counter thread 2: 99
counter thread 2: 100
counter thread 2: 101
counter thread 2: 102
counter thread 2: 103
counter thread 2: 104
counter thread 2: 105
counter thread 2: 106
counter thread 2: 107
counter thread 2: 108
counter thread 2: 109
counter thread 2: 110
counter thread 2: 111
counter thread 2: 112
counter thread 2: 113
counter thread 2: 114
counter thread 2: 115
counter thread 2: 116
counter thread 2: 117
counter thread 2: 118
counter thread 2: 119
counter thread 2: 120
 xx Thread 2 kết thúc.
Giá trị counter cuối cùng là: 120

```