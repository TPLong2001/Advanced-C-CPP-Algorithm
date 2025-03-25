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
