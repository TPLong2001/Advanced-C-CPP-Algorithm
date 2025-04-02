/***************************************************************************
 * @file    Binary_search_tree.h
 * @brief   Chuyển đổi danh sách liên kết thành cây nhị phân và tìm kiếm nhị phân.
 * @details Chương trình xây dựng danh sách liên kết đơn, sau đó chuyển đổi danh sách
 *          thành cây nhị phân tìm kiếm (BST). Hỗ trợ thêm node, tìm điểm giữa danh sách,
 *          và thực hiện tìm kiếm nhị phân.
 * @version 1.0
 * @date    2025-03-25
 * @author  Long Truong
 ***************************************************************************/
/* ===================================================[ Guard End ]===================================================*/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/* ============================================[ INCLUDE FILE ]=============================================*/
#include <stdio.h>              /**< Thư viện chứa hàm in ra màn hình >**/
#include <stdlib.h>             /**< Thư viện chứa hàm malloc >**/
#include <string.h>             /**< Thư viện thao tác với chuỗi >**/

/* ===========================================[ TYPE DEFINITIONS ]==========================================*/
/**
 * @struct  User
 * @brief   Cấu trúc lưu thông tin người dùng.
 * @details Cấu trúc này chứa tên, tuổi, địa chỉ và số điện thoại của người dùng.
 */
typedef struct User{
    char *name;                 /**< Tên của người dùng */
    int   age;                  /**< Tuổi của người dùng */
    char *addr;                 /**< Tuổi của người dùng */
    char *phone;                /**< Số điện thoại của người dùng */
} User;


 /**
  * @struct  Node
  * @brief   Cấu trúc của một node trong danh sách liên kết đơn.
  */
typedef struct Node{
    User user;                  /**< Giá trị của node */
    struct Node *next;          /**< Con trỏ đến node tiếp theo */
} Node;
 

/**
  * @struct  CenterPoint
  * @brief   Cấu trúc của một node trong cây nhị phân tìm kiếm.
  */
typedef struct CenterPoint{
     User user;                  /**< Giá trị của node */
     struct CenterPoint *left;   /**< Con trỏ đến node con trái */
     struct CenterPoint *right;  /**< Con trỏ đến node con phải */
 } CenterPoint;


extern int (*compareFunction)(const void*,const void*);      /**< Con trỏ hàm lựa chọn hàm cần dùng so sánh */   

/* ========================================[ FUNCTION INPLEMENTATION ]======================================*/
/***
  * @brief   Hàm so sánh theo Tên
  * @details Hàm so sánh chuỗi tên 2 đối tượng truyền vào
  * @param   obj1   Đối tượng thứ nhất cần so sánh.
  * @param   obj2   Đối tượng thứ nhất cần so sánh.
  * @return  int    Độ lệch ký tự khác nhau đầu tiền trong 
  *                 tên của obj1 và obj2.
  ***/
int compareByName(const void *obj1, const void *obj2);


/***
  * @brief   Hàm so sánh theo Số điện thoại
  * @details Hàm so sánh chuỗi Số điện thoại 2 đối tượng truyền vào
  * @param   obj1   Đối tượng thứ nhất cần so sánh.
  * @param   obj2   Đối tượng thứ nhất cần so sánh.
  * @return  int    Độ lệch ký tự khác nhau đầu tiền trong 
  *                 Số điện thoại của obj1 và obj2.
  ***/
int conpareByPhoneNumber(const void *obj1, const void *obj2);


/**
 * @brief   In thông tin User.
 * @details in ra thông tin của user truyền vào.
 * @param   user  Đối tượng user cần hiển thị.
 * @return  void
 **/
void print_user(User user);


/**
 * @brief   In danh sách liên kết.
 * @details Duyệt danh sách liên kết và in ra từng phần tử.
 * @param   head  Con trỏ đến danh sách liên kết.
 * @return  void
 **/
void print_list(Node *head);


/**
  * @brief   Thêm node vào danh sách liên kết và sắp xếp theo thứ tự tăng dần.
  * @param   head   Con trỏ đến con trỏ head của danh sách liên kết.
  * @param   user   Dữ liệu user cần thêm vào danh sách.
  * @return  void
  */
void add_node(Node **head, User user);


/**
 * @brief   Xây dựng cây nhị phân từ danh sách liên kết.
 * @details Tìm điểm giữa danh sách và chia danh sách thành cây nhị phân tìm kiếm.
 * @param   head   Con trỏ đến danh sách liên kết.
 * @param   start  Vị trí bắt đầu của danh sách.
 * @param   end    Vị trí kết thúc của danh sách.
 * @return  CenterPoint*   Gốc của cây nhị phân tìm kiếm.
 */
CenterPoint *buildTree(Node *head, int start, int end);


/**
 * @brief   Chuyển danh sách liên kết thành cây nhị phân tìm kiếm (BST).
 * @details Tính độ dài danh sách liên kết và gọi `buildTree()` để xây dựng BST.
 * @param   head  Con trỏ đến danh sách liên kết.
 * @return  CenterPoint*  Gốc của cây nhị phân tìm kiếm.
 */
CenterPoint *centerPoint(Node *head);


/**
 * @brief   Thực hiện tìm kiếm nhị phân trên cây BST.
 * @details Duyệt cây nhị phân để tìm kiếm giá trị cần tìm.
 * @param   root   Gốc của cây nhị phân.
 * @param   user   Dữ liệu user cần tìm.
 * @return  CenterPoint*   Trả về con trỏ đến node tìm thấy, NULL nếu không tìm thấy.
 */
CenterPoint *binarySearch(CenterPoint *root, User user);


/* ===================================================[ Guard End ]===================================================*/
#endif // BINARY_SEARCH_TREE_H