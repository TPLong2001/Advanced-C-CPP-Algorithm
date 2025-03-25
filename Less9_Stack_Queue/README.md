---

# BÀI 9: STACK - QUEUE

## Tổng quan

Cấu trúc dữ liệu là cách __tổ chức__, __lưu trữ__ dữ liệu để chúng có thể được __truy cập và sử dụng__ một cách hiệu quả, đóng vai trò quan trọng trong việc giải quyết các bài toán và tối ưu hóa thuật toán, vì nó ảnh hưởng trực tiếp đến tốc độ thực thi và tính phức tạp của chương trình.  

Cấu trúc dữ liệu được phân làm 2 loại chính:  
- Cấu trúc dữ liệu tuyến tính (Linear Data Structure): __mảng__ (Array), __ngăn xếp__ (Stack), __hàng đợi__ (Queue), __danh sách liên kết__ (Linked List).
- Cấu trúc dữ liệu phi tuyến tính (Non-linear Data Structure): __đồ thị__ (Graphs), __cây__ (Trees).


## Stack (Ngăn xếp)

__Stack__ (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc "__Last In, First Out__" (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra.   

__Các thao tác cơ bản trên stack bao gồm:__

- Push: Thêm một phần tử vào đỉnh ngăn xếp.
- Pop: Loại bỏ và trả về phần tử ở đỉnh ngăn xếp.
- Peek/Top: Trả về phần tử ở đỉnh ngăn xếp mà không loại bỏ nó.

__Ứng dụng:__ 
- Duyệt biểu thức toán học và xử lý dấu ngoặc.
- Quản lý lời gọi hàm trong ngôn ngữ lập trình.
- Thuật toán duyệt đồ thị (DFS - Depth First Search).

__Ví dụ:__
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRINT_POP(stack)    if(peak(*stack) != STACK_EMPTY) printf("Element pop: %d\n", pop(stack));
#define PRINT_PEAK(stack)   if(peak(stack) != STACK_EMPTY) printf("Element peak: %d\n", peak(stack));
#define STACK_EMPTY -1

typedef struct {
    int *item;
    int top;
    int size;
} Stack;


// Khởi tạo
int init_Stack(Stack *stack, int newSize)
{
    stack->size = newSize;
    stack->item = (int *)malloc(newSize * sizeof(int));
    stack->top = STACK_EMPTY;
}

// Kiểm tra rỗng
bool isEmpty(Stack stack)
{
    return stack.top == STACK_EMPTY;
}

// Kiểm tra đầy
bool isFull(Stack stack)
{
    return stack.top == stack.size - 1;
}

// Thêm phẩn tử
void push(Stack *stack, int data)
{
    if(isFull(*stack))
    {
        printf("Stack Full!\n");
    }else{
        stack->item[++stack->top] = data;
    }
}

// Xóa phần tử
int pop(Stack *stack){
    int data;
    if(isEmpty(*stack))
    {
        printf("Stack Empty!\n");
        return STACK_EMPTY;
    }else{
          data = stack->item[stack->top];
          stack->item[stack->top--] = 0;
          return data;
    }
}

// Đọc phần tử
int peak(Stack stack){
    if(isEmpty(stack))
    {
        printf("Stack Empty!\n");
        return STACK_EMPTY;
    }else{
          return stack.item[stack.top];
    } 
}

void displayStack(Stack stack)
{
    if(stack.top < 0){
        printf("\n");
        printf("Stack List Empty!\n");
        printf("\n");
    }else{
        printf("\n");
        printf("Display element:\n");
        for(int i = stack.top; i >= 0 ; i--){
            printf("Element %d: %d\n", i, stack.item[i]);
        }
        printf("\n");
    }
}

int main(){

    Stack stack1;
    init_Stack(&stack1, 6);

    push(&stack1, 1);
    push(&stack1, 2);
    push(&stack1, 3);
    push(&stack1, 4);
    push(&stack1, 5);

    displayStack(stack1);

    // printf("Element peak: %d\n", peak(stack1));
    PRINT_PEAK(stack1);
    // printf("Element pop: %d\n", pop(&stack1));
    PRINT_POP(&stack1);


    displayStack(stack1);

    printf("Element pop: %d\n", pop(&stack1));

    displayStack(stack1);

    push(&stack1, 43);
    push(&stack1, 33);
    push(&stack1, 85);
    push(&stack1, 26);

    displayStack(stack1);

    // printf("Element pop: %d\n", pop(&stack1));
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);

    displayStack(stack1);

    return 0;
}
```
__Kết quả:__
```c
Display element:
Element 4: 5    
Element 3: 4    
Element 2: 3    
Element 1: 2    
Element 0: 1    

Element peak: 5 
Element pop: 5  

Display element:
Element 3: 4
Element 2: 3
Element 1: 2
Element 0: 1

Element pop: 4

Display element:
Element 2: 3
Element 1: 2
Element 0: 1

Stack Full!

Display element:
Element 5: 85
Element 4: 33
Element 3: 43
Element 2: 3
Element 1: 2
Element 0: 1

Element pop: 85
Element pop: 33
Element pop: 43
Element pop: 3
Element pop: 2
Element pop: 1
Stack Empty!

Stack List Empty!
```

## Queue (Hàng đợi)

__Queue__ là một cấu trúc dữ liệu tuân theo nguyên tắc "__First In, First Out__" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra.   

__Các thao tác cơ bản trên queue bao gồm:__

- `enqueue`: Thêm một phần tử vào cuối hàng đợi.
- `dequeue`: Loại bỏ và trả về phần tử ở đầu hàng đợi.
- `rear`/`front`: Trả về phần tử ở cuối / đầu hàng đợi mà không loại bỏ nó.
- Kiểm tra hàng đợi đầy/rỗng.

__Ứng dụng:__ 
- Truyền/nhận dữ liệu từ vi điều khiển.
- Quản lý tác vụ trong các hệ thống điều hành.
- Thuật toán duyệt đồ thị (BFS - Breadth First Search).

__Hàng đợi tuyến tính (Linear Queue):__  

Đặc điểm của Hàng đợi Tuyến tính:

- Nếu `rear` đã đạt tới max, thì `queue` sẽ được coi là đầy và không thể thêm phần tử mới, ngay cả khi phía trước còn khoảng trống do các phần tử đã bị xóa.
- Chỉ có thể thêm phần tử mới khi đã `dequeue` toàn bộ các phần tử hiện có (tức là `queue` rỗng hoàn toàn và `front` được reset về vị trí ban đầu).

__Ví dụ:__
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRINT_DEQUEUE(liQueue)  if(front(liQueue) != QUEUE_EMPTY) printf("Dequeue %d\n", dequeue(&liQueue));

typedef struct
{
    int *item;  // mảng lưu trữ giá trị các phần tử
    int size;   // số lượng phần tử tối đa có thể đưa vào
    int front;  // chỉ số của phần tử đầu hàng đợi
    int rear;   // chỉ số của phần tử cuối hàng đợi
} Queue;

// khởi tạo hàng đợi
void initialize(Queue *queue, int size)
{
    queue->size  = size;
    queue->item  = (int*)malloc(size * sizeof(int));
    queue->front = queue->rear = -1;
}

// kiểm tra hàng đợi đầy
bool isFull(Queue queue)
{
    return (queue.rear == queue.size - 1);
}

// kiểm tra hàng đợi rỗng
bool isEmpty(Queue queue)
{
    return (queue.front == -1);
}

// thêm phần tử vào cuối hàng đợi
void enqueue(Queue *queue, int data)
{
    if (isFull(*queue))
    {
        printf("QUEUE IS FULL!\n");
        return;
    }
    else
    {
        if (queue->front == -1) queue->front = queue->rear = 0;
        else queue->rear++;
        queue->item[queue->rear] = data;
        printf("Enqueue data %d\n", data);
    }
}

#define QUEUE_EMPTY -1

// xóa phần tử đầu hàng đợi
int dequeue(Queue *queue)
{
    if (isEmpty(*queue))
    {
        printf("QUEUE IS EMPTY!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->item[queue->front];
        queue->item[queue->front] = 0;
        if (queue->front == queue->rear)
        {
            queue->front = queue->rear = -1;
        }
        else
        {
            queue->front++;
        }
        return dequeue_value;
    }
}

void display(Queue queue)
{
    if (isEmpty(queue))
    {
        printf("QUEUE IS EMPTY!\n");
    }
    else
    {
        printf("Queue: ");

        for (int i=queue.front; i<=queue.rear; i++)
        {
            printf("%d ", queue.item[i]);
        }
        printf("\n");
    }
}

int front(Queue queue)
{
    if (isEmpty(queue))
    {
        printf("QUEUE IS EMPTY!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.item[queue.front];
    }
}

int rear(Queue queue)
{
    if (isEmpty(queue))
    {
        printf("QUEUE IS EMPTY!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.item[queue.rear];
    }
}

int main(int argc, char const *argv[])
{
    Queue liQueue;

    initialize(&liQueue, 5);

    enqueue(&liQueue, 1);
    enqueue(&liQueue, 2);
    enqueue(&liQueue, 3);
    enqueue(&liQueue, 4);
    
    printf("Front: %d\n", front(liQueue));
    printf("Rear: %d\n", rear(liQueue));

    display(liQueue);

    // printf("Dequeue %d\n", dequeue(&liQueue));
    PRINT_DEQUEUE(liQueue);
    PRINT_DEQUEUE(liQueue);
    PRINT_DEQUEUE(liQueue);
    PRINT_DEQUEUE(liQueue);

    display(liQueue);

    enqueue(&liQueue, 5);
    enqueue(&liQueue, 6);
    enqueue(&liQueue, 7);
    enqueue(&liQueue, 8);
   
    PRINT_DEQUEUE(liQueue);
    PRINT_DEQUEUE(liQueue);

    enqueue(&liQueue, 10);

    return 0;
}

```

__Kết quả:__
```c
Enqueue data 1
Enqueue data 2
Enqueue data 3
Enqueue data 4
Front: 1
Rear: 4
Queue: 1 2 3 4
Dequeue 1
Dequeue 2
Dequeue 3
Dequeue 4
QUEUE IS EMPTY!
Enqueue data 5
Enqueue data 6
Enqueue data 7
Enqueue data 8
Dequeue 5
Dequeue 6
Enqueue data 10
```

__Hàng đợi vòng (Circular Queue):__  

Đặc điểm của Hàng đợi vòng:

- Trong hàng đợi tuyến tính: Khi `dequeue()`, phần tử bị xóa nhưng không thể sử dụng lại ô nhớ.

- Trong hàng đợi vòng: Khi phần tử được xóa, vị trí đó có thể dùng lại nhờ chỉ số front và rear quay vòng.

__Ví dụ:__
```c
#include <stdio.h>
#include <stdlib.h>

#define PRINT_DEQUEUE(queue)  if(front(queue) != QUEUE_EMPTY) printf("Dequeue -> %d\n", dequeue(&queue));

typedef struct
{
    int *items; // mảng lưu trữ giá trị các phần tử
    int size;   // kích thước của hàng đợi
    int front;  // chỉ số phần tử đầu hàng đợi
    int rear;   // chỉ số phần tử cuối hàng đợi
} Queue;

// khởi tạo hàng đợi
void queue_Init(Queue *queue, int size)
{
    queue->items = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
}

// kiểm tra hàng đợi rỗng
int queue_IsEmpty(Queue queue)
{
    return (queue.front == -1);
}

// kiểm tra hàng đợi đầy
int queue_IsFull(Queue queue)
{
    return (queue.rear + 1) % queue.size == queue.front;
}

// thêm phần tử vào cuối hàng đợi
void enqueue(Queue *queue, int data)
{
    if (queue_IsFull(*queue))
    {
        // nếu queue đầy thì không cho thêm phần tử vào
        printf("QUEUE IS FULL!\n");
    }
    else
    {
        if (queue_IsEmpty(*queue))
        {
            queue->front = queue->rear = 0;
        }
        else
        {
            queue->rear = (queue->rear + 1) % queue->size;
        }
        queue->items[queue->rear] = data;
        printf("Enqueued %d\n", data);
    }
}

#define QUEUE_EMPTY -1

// xóa phần tử từ đầu hàng đợi
int dequeue(Queue *queue)
{
    if (queue_IsEmpty(*queue))
    {
        // nếu queue rỗng thì không cho xóa
        printf("Hàng đợi rỗng\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->items[queue->front];
        queue->items[queue->front] = 0;
        if (queue->front == queue->rear)
        {
            queue->front = queue->rear = -1;
        }
        else
        {
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeue_value;
    }
}

// lấy giá trị của phần tử đứng đầu hàng đợi (front)
int front(Queue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Queue is empty!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.items[queue.front];
    }
}

// lấy giá trị của phần tử đứng cuối hàng đợi (rear)
int rear(Queue queue)
{
    if (queue_IsEmpty(queue))
    {
        printf("Queue is empty\n");
        return QUEUE_EMPTY;
    }
    else
    {
        return queue.items[queue.rear];
    }
}

// Hiển thị các phần tử
void display(Queue q)
{
    if (queue_IsEmpty(q))
    {
        printf("Queue List is empty!\n");
        return;
    }
    printf("QUEUE LIST: ");
    int i = q.front;

    while (1)
    {
        printf("%d ", q.items[i]);
        if (i == q.rear) break;
        i = (i + 1) % q.size;
    }
    printf("\n");
}


int main(int argc, char const *argv[])
{
    Queue queue;
   
    queue_Init(&queue, 5);

    enqueue(&queue, 10);
    enqueue(&queue, 15);
    enqueue(&queue, 20);
    enqueue(&queue, 25);
 

    display(queue);

    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n", rear(queue));

    // printf("Dequeued %d\n", dequeue(&queue));
    PRINT_DEQUEUE(queue);
    PRINT_DEQUEUE(queue);
    // PRINT_DEQUEUE(queue);
    // PRINT_DEQUEUE(queue);
    // PRINT_DEQUEUE(queue);


    display(queue);

    enqueue(&queue, 30);
    enqueue(&queue, 50);
    display(queue);

    printf("Front element: %d\n", front(queue));
    printf("Rear element: %d\n", rear(queue));

    return 0;
}

```

__Kết quả:__
```c
Enqueued 10
Enqueued 15
Enqueued 20
Enqueued 25
QUEUE LIST: 10 15 20 25
Front element: 10
Rear element: 25
Dequeue -> 10
Dequeue -> 15
QUEUE LIST: 20 25
Enqueued 30
Enqueued 50
QUEUE LIST: 20 25 30 50
Front element: 20
Rear element: 50
```

## SO SÁNH
| **Đặc Điểm**  | **Ngăn Xếp (Stack)** | **Hàng Đợi (Queue)** |
|--------------|-------------------|-------------------|
| **Nguyên tắc** | LIFO (Last In, First Out) | FIFO (First In, First Out) |
| **Thao tác chính** | Push, Pop, Peek | Enqueue, Dequeue, front, rear |
| **Truy cập** | Truy cập phần tử cuối cùng (đỉnh) | Truy cập phần tử đầu tiên (front) |
| **Ứng dụng** | Quản lý lời gọi hàm, xử lý dấu ngoặc, thuật toán DFS | Quản lý tác vụ, xử lý yêu cầu hệ thống, thuật toán BFS |
| **Sử dụng** | Xử lý các tác vụ theo nguyên tắc LIFO như quản lý lời gọi hàm hoặc duyệt đồ thị theo chiều sâu | Xử lý các tác vụ theo nguyên tắc FIFO như quản lý tác vụ hoặc duyệt đồ thị theo chiều rộng |

