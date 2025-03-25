/***************************************************************************
 * @file    queue_ring.c
 * @brief   Định nghõa các hàm cho cấu trúc liên quan đến hàng đợi vòng (circular queue)
 * @details File này định nghĩa các hàm sử dụng trong hàng đợi vòng, bao gồm
 *          khởi tạo hàng đợi với kích thước cụ thể, thêm, xóa các thành phần vào hàng đợi, đọc và hiển thị các thành phần trong hàng đợi.
 * @version 1.0
 * @date    2025-03-11
 * @author  LongTruong
 ***************************************************************************/

/* ==================================================[ INCLUDE FILE ]==================================================*/
#include "queue_ring.h"

/* ==============================================[ FUNCTION INPLEMENTATION ]==============================================*/
/****************************************************************************
 * @brief   Khởi tạo Hàng đợi.
 * @details Hàm này khởi tạo hàng đợi với kích thước cố định.
 *          Biến size truyền vào kích thước tối đa của hàng đợi.
 * @param   queue   con trỏ trỏ đến hàng đợi.
 * @param   size    kích thước tối đa của hàng đợi.
 * @return  void
 ***************************************************************************/
void queue_Init(Queue *queue, int size)
{
    queue->items = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
}


/***************************************************************************
 * @brief   Kiểm tra hàng đợi có rỗng không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Neus hàng đợi rỗng.
 * @return  false   Nếu hàng đợi không rỗng.
 ***************************************************************************/
int queue_IsEmpty(Queue queue)
{
    return (queue.front == -1);
}


/***************************************************************************
 * @brief   Kiểm tra hàng đợi có đầy không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Neus hàng đợi đầy.
 * @return  false   Nếu hàng đợi không đầy.
 ***************************************************************************/
int queue_IsFull(Queue queue)
{
    return (queue.rear + 1) % queue.size == queue.front;
}


/***************************************************************************
 * @brief   Thêm phần tử vào cuối hàng đợi.
 * @param   queue   Con trỏ trỏ đến hàng đợi.
 * @param   data    Dữ liệu cần thêm vào hàng đợi.
 * @return  void
***************************************************************************/
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


/***************************************************************************
 * @brief   Xóa phần tử từ đầu hàng đợi.
 * @param   queue   Con trỏ trỏ đến hàng đợi.
 * @return  int     Giá trị của phần tử đầu hàng đợi.
***************************************************************************/
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


/***************************************************************************
 * @brief   Đọc giá trị của phần tử đứng đầu hàng đợi.
 * @param   queue   Hàng đợi cần đọc.
 * @return  int     Giá trị của phần tử đầu hàng đợi.
***************************************************************************/
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


/***************************************************************************
 * @brief   Đọc giá trị của phần tử đứng cuối hàng đợi.
 * @param   queue   Hàng đợi cần đọc.
 * @return  int     Giá trị của phần tử đầu hàng đợi.
***************************************************************************/
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


/***************************************************************************
 * @brief   Hiển thị các phần tử trong hàng đợi.
 * @param   queue   Hàng đợi cần đọc.
 * @return  void
 ***************************************************************************/
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