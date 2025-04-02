#include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 /**
  * @struct  Node
  * @brief   Cấu trúc của một node trong danh sách liên kết đơn.
  */
 typedef struct Node
 {
     int data;          /**< Giá trị của node */
     struct Node *next; /**< Con trỏ đến node tiếp theo */
 } Node;
 
 /**
  * @brief   Thêm node vào danh sách liên kết và sắp xếp theo thứ tự tăng dần.
  * @param   head   Con trỏ đến con trỏ head của danh sách liên kết.
  * @param   value  Giá trị cần thêm vào danh sách.
  * @return  void
  */
 void add_node(Node **head, int value)
 {
     Node *new_node = (Node *)malloc(sizeof(Node));
     new_node->data = value;
     new_node->next = NULL;
 
     if (*head == NULL || (*head)->data >= value)
     {
         new_node->next = *head;
         *head = new_node;
         return;
     }
 
     Node *current = *head;
     while (current->next != NULL && current->next->data < value)
     {
         current = current->next;
     }
 
     new_node->next = current->next;
     current->next = new_node;
 }
 
 /**
  * @struct  CenterPoint
  * @brief   Cấu trúc của một node trong cây nhị phân tìm kiếm.
  */
 typedef struct CenterPoint
 {
     int value;                  /**< Giá trị của node */
     struct CenterPoint *left;   /**< Con trỏ đến node con trái */
     struct CenterPoint *right;  /**< Con trỏ đến node con phải */
 } CenterPoint;
 
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
     root->value = node->data;
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
  * @param   value  Giá trị cần tìm.
  * @return  CenterPoint*   Trả về con trỏ đến node tìm thấy, NULL nếu không tìm thấy.
  */
 CenterPoint *binarySearch(CenterPoint *root, int value)
 {
     static int loop = 0;
     loop++;
     printf("Số lần lặp: %d\n", loop);
 
     if (root == NULL) return NULL;
 
     if (root->value == value)
     {
         return root;
     }
     else if (value < root->value)
     {
         return binarySearch(root->left, value);
     }
     else
     {
         return binarySearch(root->right, value);
     }
 }
 
 /**
  * @brief   In danh sách liên kết.
  * @details Duyệt danh sách liên kết và in ra từng phần tử.
  * @param   head  Con trỏ đến danh sách liên kết.
  * @return  void
  */
 void print_list(Node *head)
 {
     while (head != NULL)
     {
         printf("%d ", head->data);
         head = head->next;
     }
     printf("\n");
 }
 
 
 int main()
 {
     Node *head = NULL;
 
     /**
      * @brief   Tạo ngẫu nhiên 10000 node trong danh sách liên kết.
      */
     srand(time(NULL));
     for (int i = 0; i < 10000; i++)
     {
         int value = rand() % 10000 + 1;
         add_node(&head, value);
     }
 
     // add_node(&head, 5639); // Thêm node cụ thể nếu cần
 
     /**
      * @brief   In danh sách liên kết.
      */
     print_list(head);
 
     /**
      * @brief   Chuyển danh sách liên kết thành cây nhị phân tìm kiếm (BST).
      */
     CenterPoint *ptr = centerPoint(head);
 
     /**
      * @brief   Thực hiện tìm kiếm nhị phân trong cây BST.
      * @details Tìm kiếm giá trị ngẫu nhiên vừa được thêm vào danh sách.
      */
     CenterPoint *result = binarySearch(ptr, rand() % 10000 + 1);
     if (result != NULL)
     {
         printf("Tìm thấy giá trị: %d\n", result->value);
     }
     else
     {
         printf("Không tìm thấy giá trị.\n");
     }
     return 0;
 }