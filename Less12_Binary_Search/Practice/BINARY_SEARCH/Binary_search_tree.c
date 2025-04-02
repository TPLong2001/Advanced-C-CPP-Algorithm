/***************************************************************************
 * @file    Binary_search_tree.c
 * @brief   Triển khai hàm chuyển đổi danh sách liên kết thành cây nhị phân và tìm kiếm nhị phân.
 * @details Chương trình xây dựng danh sách liên kết đơn, sau đó chuyển đổi danh sách
 *          thành cây nhị phân tìm kiếm (BST). Hỗ trợ thêm node, tìm điểm giữa danh sách,
 *          và thực hiện tìm kiếm nhị phân.
 * @version 1.0
 * @date    2025-03-25
 * @author  Long Truong
 ***************************************************************************/
/* ============================================[ INCLUDE FILE ]============================================*/
#include "Binary_search_tree.h"

/* ===========================================[ TYPE DEFINITIONS ]==========================================*/
int (*compareFunction)(const void*, const void*) = NULL;    /**< Con trỏ hàm lựa chọn hàm cần dùng so sánh */

/* ========================================[ FUNCTION INPLEMENTATION ]======================================*/
/**
  * @brief   Thêm dữ liệu của user vào node.
  * @details Cấp phát động vầ thêm dữ liệu của user
  *          Vào node.
  * @param   node   Con trỏ đến node cần thêm dữ liệu.
  * @param   user   Dữ liệu user cần thêm vào node.
  * @return  void
  */
static void add_userToNode(Node *node, User user)
{
    node->user.name = (char *)malloc(strlen(user.name) + 1);
    node->user.addr = (char *)malloc(strlen(user.addr) + 1);
    node->user.phone = (char *)malloc(strlen(user.phone) + 1);

    strcpy(node->user.name, user.name);
    node->user.age = user.age;
    strcpy(node->user.addr, user.addr);
    strcpy(node->user.phone, user.phone);
}


/**
  * @brief   Thêm dữ liệu user từ Node vào BST.
  * @details Cấp phát động dữ liệu của user trong point của BST 
  *          vầ thêm dữ liệu của user từ node vào.
  * @param   list   Con trỏ đến point trong BST cần thêm dữ liệu.
  * @param   node   Node cần lấy dữ liệu user để thêm vào BST.
  * @return  void
  */
static void add_nodeToList(CenterPoint *list, Node *node)
{
    list->user.name = (char *)malloc(strlen(node->user.name) + 1);
    list->user.addr = (char *)malloc(strlen(node->user.addr) + 1);
    list->user.phone = (char *)malloc(strlen(node->user.phone) + 1);

    strcpy(list->user.name, node->user.name);
    list->user.age = node->user.age;
    strcpy(list->user.addr, node->user.addr);
    strcpy(list->user.phone, node->user.phone);
}


/**
  * @brief   Hàm so sánh chuỗi
  * @details Hàm so sánh 2 chuỗi truyền vào theo mã ASCII và
  *          trả về độ lệch của ký tự khác nhau đầu tiền giữa 
  *          chuôi str1 và str2
  * @param   str1   Chuỗi thứ nhất cần so sánh.
  * @param   str2   Chuỗi thứ nhất cần so sánh.
  * @return  int    Độ lệch ký tự khác nhau đầu tiền giữa str1 và str2
  */
static int compareString(const char *str1, const char *str2)
{
    while((*str1 == *str2) && *str1){
        str1++;
        str2++;
    }
    return *(const char*)str1 - *(const char*)str2;
}


/***
  * @brief   Hàm so sánh theo Tên
  * @details Hàm so sánh chuỗi tên 2 đối tượng truyền vào
  * @param   obj1   Đối tượng thứ nhất cần so sánh.
  * @param   obj2   Đối tượng thứ nhất cần so sánh.
  * @return  int    Độ lệch ký tự khác nhau đầu tiền trong 
  *                 tên của obj1 và obj2.
  ***/
int compareByName(const void *obj1, const void *obj2)
{
    User *user1 = (User *)obj1;
    User *user2 = (User *)obj2;
    return compareString(user1->name, user2->name);
}


/***
  * @brief   Hàm so sánh theo Số điện thoại
  * @details Hàm so sánh chuỗi Số điện thoại 2 đối tượng truyền vào
  * @param   obj1   Đối tượng thứ nhất cần so sánh.
  * @param   obj2   Đối tượng thứ nhất cần so sánh.
  * @return  int    Độ lệch ký tự khác nhau đầu tiền trong 
  *                 Số điện thoại của obj1 và obj2.
  ***/
int conpareByPhoneNumber(const void *obj1, const void *obj2)
{
    User *user1 = (User *)obj1;
    User *user2 = (User *)obj2;
    return compareString(user1->phone, user2->phone);
}


/**
 * @brief   In thông tin User.
 * @details in ra thông tin của user truyền vào.
 * @param   user  Đối tượng user cần hiển thị.
 * @return  void
 **/
void print_user(User user){
    printf("Name: %s \n", user.name);
    printf("Age: %d \n", user.age);
    printf("Address: %s \n", user.addr);
    printf("Phone number: %s \n\n", user.phone);
}

/**
 * @brief   In danh sách liên kết.
 * @details Duyệt danh sách liên kết và in ra từng phần tử.
 * @param   head  Con trỏ đến danh sách liên kết.
 * @return  void
 **/
void print_list(Node *head)
{
    while (head != NULL)
    {
        print_user(head->user);
        head = head->next;
    }
    printf("\n");
}


 /**
  * @brief   Thêm node vào danh sách liên kết và sắp xếp theo thứ tự tăng dần.
  * @param   head   Con trỏ đến con trỏ head của danh sách liên kết.
  * @param   user   Dữ liệu user cần thêm vào danh sách.
  * @return  void
  */
 void add_node(Node **head, User user)
 {
     Node *new_node = (Node *)malloc(sizeof(Node));
     add_userToNode(new_node, user);
     new_node->next = NULL;
     
     // Điều kiện so sánh    
     if (*head == NULL || compareFunction(&(*head)->user, &user) >= 0)
     {
         new_node->next = *head;
         *head = new_node;
         return;
     }
     
     Node *current = *head;

     // Điều kiện so sánh
     while (current->next != NULL && compareFunction(&current->next->user, &user) < 0)
     {
         current = current->next;
     }
 
     new_node->next = current->next;
     current->next = new_node;
 }
 

 /**
  * @brief   Xây dựng cây nhị phân từ danh sách liên kết.
  * @details Tìm điểm giữa danh sách và chia danh sách thành cây nhị phân tìm kiếm.
  * @param   head   Con trỏ đến danh sách liên kết.
  * @param   start  Vị trí bắt đầu của danh sách.
  * @param   end    Vị trí kết thúc của danh sách.
  * @return  CenterPoint*   Gốc của cây nhị phân tìm kiếm.
  */
 CenterPoint *buildTree(Node *head, int start, int end)
 {
     if (head == NULL || start > end)
     {
         return NULL;
     }
 
     int mid = (start + end) / 2;
     Node *node = head;
 
     for (int i = start; i < mid; i++)
     {
         if (node->next == NULL) break;
         node = node->next;
     }
 
     CenterPoint *root = (CenterPoint *) malloc(sizeof(CenterPoint));

     add_nodeToList(root,node);
     root->left = buildTree(head, start, mid - 1);
     root->right = buildTree(node->next, mid + 1, end);
     return root;
 }
  
 /**
  * @brief   Chuyển danh sách liên kết thành cây nhị phân tìm kiếm (BST).
  * @details Tính độ dài danh sách liên kết và gọi `buildTree()` để xây dựng BST.
  * @param   head  Con trỏ đến danh sách liên kết.
  * @return  CenterPoint*  Gốc của cây nhị phân tìm kiếm.
  */
 CenterPoint *centerPoint(Node *head)
 {
     int length = 0;
     Node *node = head;
     while (node != NULL)
     {
         node = node->next;
         length++;
     }
     return buildTree(head, 0, length - 1);
 }
 
/**
 * @brief   Thực hiện tìm kiếm nhị phân trên cây BST.
 * @details Duyệt cây nhị phân để tìm kiếm giá trị cần tìm.
 * @param   root   Gốc của cây nhị phân.
 * @param   user   Dữ liệu user cần tìm.
 * @return  CenterPoint*   Trả về con trỏ đến node tìm thấy, NULL nếu không tìm thấy.
 */
 CenterPoint *binarySearch(CenterPoint *root, User user)
 {
     static int loop = 0;
     loop++;
     printf("Số lần lặp: %d\n", loop);
 
     if (root == NULL) return NULL;

     // Điều kiện tìm kiếm
     if (compareFunction(&root->user, &user) == 0)
     {
         return root;
     }
     else if (compareFunction(&root->user, &user) > 0)
     {
         return binarySearch(root->left, user);
     }
     else
     {
         return binarySearch(root->right, user);
     }
 }
 
