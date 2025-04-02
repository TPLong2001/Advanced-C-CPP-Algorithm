
---

# BÀI 12: Bubble Sort, Binary Search, Binary Search Tree

## Bubble Sort

Thuật toán sắp xếp nổi bọt (__Bubble Sort__) hoạt động dựa trên nguyên tắc hoán đổi các phần tử liền kề để đưa phần tử lớn hơn về cuối dãy (hoặc phần tử nhỏ hơn về đầu dãy).  

__Thuật toán gồm các bước sau:__
- Duyệt qua danh sách từ đầu đến cuối.
- So sánh hai phần tử liền kề, nếu phần tử trước lớn hơn phần tử sau, thì hoán đổi vị trí.
- Lặp lại quá trình cho đến khi không còn sự hoán đổi nào xảy ra (mảng đã được sắp xếp).

__Ưu điểm & Nhược điểm__  

__Ưu điểm:__

- Dễ hiểu, dễ cài đặt.
- Hiệu quả khi dữ liệu gần như đã sắp xếp.

__Nhược điểm__ 

- Hiệu suất kém với danh sách lớn.
- Chạy chậm hơn các thuật toán như Quick Sort, Merge Sort.

__Ví dụ:__
```c
#include <stdio.h>

void bubbleSort(int arr[], int n)
{
    for (int i=0; i<=n-2; i++){
        for (int j=0; j<=n-i-2; j++){
            if (arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j]   = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }  
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    bubbleSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
```

__Kết quả:__
```c
Original array: 
64 34 25 12 22 11 90 
Sorted array:
11 12 22 25 34 64 90
```

## Binary Search

Thuật toán tìm kiếm nhị phân (Binary Search) hoạt động bằng cách chia đôi mảng để tìm kiếm, thay vì duyệt tuần tự như Linear Search.  

__Nguyên tắc hoạt động:__

__B1__: **Sắp xếp mảng** (tăng dần hoặc giảm dần).  
__B2__: **So sánh phần tử giữa mảng với giá trị cần tìm**:
   - Nếu trùng → **Trả về vị trí**.  
   - Nếu nhỏ hơn → **Tìm trong nửa phải**.  
   - Nếu lớn hơn → **Tìm trong nửa trái**.  
__B3__: **Lặp lại bước 2** cho đến khi tìm thấy phần tử hoặc không còn phần tử nào để tìm.
 
__Ưu điểm:__

- Tốc độ nhanh hơn tìm kiếm tuyến tính (O(log n) so với O(n)).
- Tốt cho mảng lớn khi đã được sắp xếp.

__Nhược điểm:__

- Chỉ hoạt động trên mảng đã sắp xếp.
- Nếu mảng thay đổi liên tục, phải sắp xếp lại trước khi tìm kiếm.

__Ví dụ:__
```c
#include <stdio.h>

#define NO_FOUND -1    

int binarySearch(int* arr, int l, int r, int target)
{
    if (r >= l){
        int mid = (r + l) / 2;

        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] > target){
            return binarySearch(arr, l, mid - 1, target);
        }
        else{
            return binarySearch(arr, mid + 1, r, target);
        }
    }
    return NO_FOUND;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int result = binarySearch(arr, 0, n - 1, target);
    if (result != -1)
        printf("Phần tử %d được tìm thấy tại vị trí %d\n", target, result);
    else
        printf("Phần tử %d không tồn tại trong mảng\n", target);

    return 0;
}

```

__Kết quả:__
```c
Phần tử 7 được tìm thấy tại vị trí 3
```

## Binary Search Tree

Cây tìm kiếm nhị phân (__BST - Binary Search Tree__) là một loại cấu trúc dữ liệu cây, trong đó __mỗi nút có tối đa hai con__ và tuân theo __nguyên tắc__:  

- Cây con bên trái chứa các phần tử có giá trị nhỏ hơn nút gốc.
- Cây con bên phải chứa các phần tử có giá trị lớn hơn nút gốc.
- Quy tắc này được áp dụng đệ quy trên toàn bộ cây.

BST giúp thực hiện các thao tác tìm kiếm, chèn, xóa nhanh hơn so với danh sách liên kết hoặc mảng trong nhiều trường hợp.

__Tìm kiếm một phần tử trong cây:__  

- Nếu giá trị cần tìm trùng với giá trị của nút hiện tại → Trả về nút đó.
- Nếu nhỏ hơn → Tìm trong cây con bên trái.
- Nếu lớn hơn → Tìm trong cây con bên phải.
- Nếu duyệt đến NULL mà chưa tìm thấy → Phần tử không tồn tại trong cây.


__Ứng dụng của BST:__

- Tìm kiếm nhanh trong danh bạ, cơ sở dữ liệu.
- Lưu trữ và quản lý tập hợp dữ liệu lớn.
- Hỗ trợ bộ nhớ cache và lập chỉ mục trong hệ thống.
- Xây dựng từ điển, hệ thống tự động hoàn thành.
- Ứng dụng trong nén dữ liệu và xử lý đồ họa máy tính.

BST là nền tảng cho các cấu trúc nâng cao như AVL Tree, Red-Black Tree, B-Tree, giúp tối ưu hiệu suất tìm kiếm.

__Ví dụ:__
```c
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
    //print_list(head);
 
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
```

__Kết quả:__
```c
Số lần lặp: 1
Số lần lặp: 2
Số lần lặp: 3
Số lần lặp: 4
Số lần lặp: 5
Số lần lặp: 6
Số lần lặp: 7
Số lần lặp: 8
Số lần lặp: 9
Số lần lặp: 10
Số lần lặp: 11
Số lần lặp: 12
Số lần lặp: 13
Số lần lặp: 14
Tìm thấy giá trị: 2840
```