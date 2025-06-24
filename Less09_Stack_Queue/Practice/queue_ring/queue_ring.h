
/***************************************************************************
 * @file    queue_ring.h
 * @brief   Khai báo các hàm và cấu trúc liên quan đến hàng đợi vòng (circular queue)
 * @details File này cung cấp giao diện cho việc sử dụng hàng đợi vòng, bao gồm
 *          khởi tạo hàng đợi với kích thước cụ thể, thêm, xóa các thành phần vào hàng đợi, đọc và hiển thị các thành phần trong hàng đợi.
 * @version 1.0
 * @date    2025-03-11
 * @author  LongTruong
 ***************************************************************************/

#ifndef QUEUE_RING_H
#define QUEUE_RING_H

/* ==================================================[ INCLUDE FILE ]==================================================*/
#include <stdio.h>                                           /**< Thư viện chứa hàm in ra màn hình >**/
#include <stdlib.h>                                          /**< Thư viện chứa hàm malloc >**/

/* ================================================[ MACRO DEFINITIONS ]================================================*/
#define QUEUE_EMPTY -1                                                      /**< Giá trị trả về khi hàng đợi rỗng >**/
#define PRINT_DEQUEUE(queue)    if(front(queue) != QUEUE_EMPTY) \
                                printf("Dequeue -> %d\n", dequeue(&queue)); /**< Hàm kiểm tra hàng đợi rỗng trước khi lấy và in dữ liệu lấy ra >**/

/* ================================================[ TYPE DEFINITIONS ]================================================*/
/**
 * @brief   Cấu trúc dữ liệu của hàng đợi vòng.
 **/
typedef struct
{
    int *items;     /**< mảng lưu trữ giá trị các phần tử.  >**/
    int size;       /**< kích thước của hàng đợi.           >**/
    int front;      /**< chỉ số phần tử đầu hàng đợi.       >**/
    int rear;       /**< chỉ số phần tử cuối hàng đợi.      >**/
} Queue;


/* ==============================================[ FUNCTION INPLEMENTATION ]==============================================*/
/**
 * @brief   Khởi tạo Hàng đợi.
 * @param   queue   con trỏ trỏ đến hàng đợi.
 * @param   size    kích thước tối đa của hàng đợi.
 * @return  void
 **/
void queue_Init(Queue *queue, int size);


/**
 * @brief   Kiểm tra hàng đợi có rỗng không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Neus hàng đợi rỗng.
 * @return  false   Nếu hàng đợi không rỗng.
 **/
int queue_IsEmpty(Queue queue);


/**
 * @brief   Kiểm tra hàng đợi có đầy không.
 * @param   queue   Hàng đợi cần kiểm tra.
 * @return  true    Neus hàng đợi đầy.
 * @return  false   Nếu hàng đợi không đầy.
 **/
int queue_IsFull(Queue queue);


/**
 * @brief   Thêm phần tử vào cuối hàng đợi.
 * @param   queue   Con trỏ trỏ đến hàng đợi.
 * @param   data    Dữ liệu cần thêm vào hàng đợi.
 * @return  void
 **/
void enqueue(Queue *queue, int data);


/**
 * @brief   Xóa phần tử từ đầu hàng đợi.
 * @param   queue   Con trỏ trỏ đến hàng đợi.
 * @return  int     Giá trị của phần tử đầu hàng đợi.
 **/
int dequeue(Queue *queue);

/**
 * @brief   Đọc giá trị của phần tử đứng đầu hàng đợi.
 * @param   queue   Hàng đợi cần đọc.
 * @return  int     Giá trị của phần tử đầu hàng đợi.
 **/
int front(Queue queue);

/**
 * @brief   Đọc giá trị của phần tử đứng cuối hàng đợi.
 * @param   queue   Hàng đợi cần đọc.
 * @return  int     Giá trị của phần tử đầu hàng đợi.
 **/
int rear(Queue queue);

/**
 * @brief   Hiển thị các phần tử trong hàng đợi.
 * @param   queue   Hàng đợi cần đọc.
 * @return  void
 **/
void display(Queue q);

#endif // QUEUE_RING_H