/***************************************************************************
 * @file    LinkedList.c
 * @brief   Khai báo các hàm và cấu trúc liên quan đến danh sách liên kết đơn (single linked list)
 * @details File này cung cấp giao diện cho việc sử dụng linked list bao gồm:
 *          khởi tạo node mới, thêm, xóa các node vào các vị trí khác nhau, 
 *          Đọc và hiển thị các node hoặc list.
 * @version 1.0
 * @date    2025-03-13
 * @author  LongTruong
 ***************************************************************************/

/* =====================================================[ Guard ]====================================================*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* ============================================[ INCLUDE FILE ]============================================*/
#include <stdio.h>              /**< Thư viện chứa hàm in ra màn hình >**/
#include <stdlib.h>             /**< Thư viện chứa hàm malloc >**/
#include <stdbool.h>            /**< Thư viện chứa kiểu dữ liệu bool >**/

/* ==========================================[ MACRO DEFINITIONS ]==========================================*/
#define NODE_EMPTY -1           /**< Giá trị trả về khi danh sách rỗng >**/

/* ===========================================[ TYPE DEFINITIONS ]==========================================*/
/**
 * @brief   Cấu trúc dữ liệu của Node.
 **/
typedef struct Node
{
    int data;                   /**< Dữ liệu của node >**/
    struct Node *next;          /**< Con trỏ trỏ đến node tiếp theo >**/
} Node;

/* ========================================[ FUNCTION INPLEMENTATION ]======================================*/
/**
 * @brief   Khởi tạo Node.
 * @param   value   dữ liệu của node mới.
 * @return  Node * con trỏ trỏ đến node mới được khởi tạo.
 **/
Node *createNode(int value); 


/**
 * @brief   Thêm phần tử vào cuối danh sách liên kết
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   value   dữ liệu của node mới.
 * @return  void
 **/
void push_back(Node** array, int value);


/**
 * @brief   Thêm phần tử vào đầu danh sách liên kết
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   value   dữ liệu của node mới.
 * @return  void
 **/
void push_front(Node **array, int value);


/**
 * @brief   Thêm phần tử vào vị trí nào đó trong danh sách liên kết
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   value   dữ liệu của node mới.
 * @param   pos     vị trí cần thêm.
 * @return  void
 **/
void insert(Node **array, int value, int pos);


/**
 * @brief   Xóa phần tử cuối cùng trong danh sách liên kết
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @return  void
 **/
void pop_back(Node **array);


/**
 * @brief   Xóa phần tử ở đầu danh sách liên kết
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @return  void
 **/
void pop_front(Node **array);


/**
 * @brief   Xóa phần tử ở vị trí nào đó trong danh sách liên kết
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   pos     vị trí cần xóa.
 * @return  void
 **/
void erase(Node **array, int pos);


/**
 * @brief   Lấy giá trị của node đầu tiên trong danh sách liên kết
 * @param   array   con trỏ trỏ đến vị trí đầu danh sách liên kết.
 * @return  int     giá trị của node đầu tiên.
 **/
int front(Node *array);


/**
 * @brief   Lấy giá trị của node cuối cùng trong danh sách liên kết
 * @param   array   con trỏ trỏ đến vị trí đầu danh sách liên kết.
 * @return  int     giá trị của node cuối cùng.
 **/
int back(Node *array);


/**
 * @brief   Lấy giá trị của node tại vị trí bất kỳ trong danh sách liên kết
 * @param   array   con trỏ trỏ đến vị trí đầu danh sách liên kết.
 * @param   pos     vị trí cần lấy giá trị.
 * @return  int     giá trị của node tại vị trí pos.
 **/
int get(Node *array, int pos);


/**
 * @brief   Lấy kích thước của danh sách liên kết.
 * @param   array   con trỏ trỏ đến đầu danh sách.
 * @return  int     số lượng phần tử trong danh sách.
 **/
int size(Node *array);


/**
 * @brief   Kiểm tra danh sách có rỗng không.
 * @param   array   con trỏ trỏ đến đầu danh sách.
 * @return  true    nếu danh sách rỗng.
 * @return  false   nếu danh sách không rỗng.
 **/
bool empty(Node *array);


/**
 * @brief   Xóa toàn bộ node trong danh sách liên kết
 * @param   array   con trỏ trỏ đến vị trí đầu danh sách.
 * @return  void
 **/
void clear(Node **head);


/**
 * @brief   In ra danh sách liên kết
 * @param   array   con trỏ trỏ đến vị trí đầu danh sách.
 * @return  void
 **/
void printList(Node *array);

/* ===================================================[ Guard End ]===================================================*/
#endif // LINKEDLIST_H