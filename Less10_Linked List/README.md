---

# BÀI 10: LINKED LIST

## Tổng quan

__Linked list__ là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu.  

Một __linked list__ bao gồm một chuỗi các "__nút__" (nodes), mỗi nút là một cấu trúc có hai thành phần:  

- __Thành phần dữ liệu__: lưu thông tin về bản thân phần tử đó.
- __Thành phần liên kết__: Trỏ đến phần tử tiếp theo nó liên kết.


## Cấu Trúc 
Cấu trúc của 1 node trong Singly Linked List.
```c
/**
 * @brief   Cấu trúc dữ liệu của Node.
 **/
typedef struct Node
{
    int data;                   /**< Dữ liệu của node >**/
    struct Node *next;          /**< Con trỏ trỏ đến node tiếp theo >**/
} Node;
```

## Thao Tác Với Linked List

Ta có thể thêm, xóa phần tử vào bất kỳ vị trí nào của danh sách 1 cách dễ dàng với độ phức tạp thấp. Và các tính năng khác như dưới đây.

__Ví dụ:__
```c
Node *createNode(int value); 
void push_back(Node** array, int value);    // them 1 node vao phia sau
void push_front(Node **array, int value);   // them 1 node vao phia truoc
void insert(Node **array, int value, int pos); // them 1 node vao mot vi tri bat ky

void pop_back(Node **array);                // xoa node cuoi cung
void pop_front(Node **array);               // xoa node dau tien
void erase(Node **array, int pos);          // xoa 1 node tai mot vi tri bat ky

int front(Node *array);                     // lay gia tri cua node dau tien
int back(Node *array);                      // lay gia tri cua node cuoi cung
int get(Node *array, int pos);              // lay gia tri cua node tai mot vi tri bat ky

int size(Node *array);                      // lay kich thuoc cua list
bool empty(Node *array);                    // kiem tra list co rong hay khong
void clear(Node **head);                    // xóa toàn bộ node
void printList(Node *array);                // in ra danh sach cua list
```

## Đặc Điểm và So Sánh

__Đặc Điểm:__  

- Được cấp phát bộ nhớ khi chạy chương trình.  
- Có thể thay đổi kích thước qua việc thêm, xóa phần tử.  
- Kích thước tối đa phụ thuộc vào bộ nhớ khả dụng của heap.  
- Các phần tử được lưu trữ ngẫu nhiên (không liên tiếp) trong heap.  

__So Sánh với Array:__  

|Array (mảng)|Linked List (danh sách liên kết)|
  |----------|-----------|
  |- Bộ nhớ được cấp phát liên tiếp nhau|- Bộ nhớ lưu trữ các node không cần liên tiếp nhau, các node chứa con trỏ liên kết đến các node cạnh nó|
  |- Kích thước cố định sau khi cấp phát|- Kích thước linh hoạt, có thể thay đổi bằng cách thêm, xóa node|
  |- Có thể truy cập bất cứ phần tử nào ngay lập tức với số chỉ của nó trong mảng|- Muốn truy cập tới phần tử thứ i phải duyệt danh sách từ vị trí đầu tới i|
  |- Thêm hoặc xóa phần tử rất khó khăn, phải dịch chuyển các phần tử khác để giữ tính liên tiếp trong bộ nhớ|- Thêm xóa rất dễ dàng bằng việc sửa con trỏ liên kết node|
  |- Bố nhớ chỉ cần lưu trữ các phần tử|- Bộ nhớ cần lưu trữ phần tử và con trỏ liên kết => tốn bộ nhớ hơn|
  |- Array được sử dụng khi ta cần sử dụng để lưu trữ mảng với số lượng phần tử đã biết trước và phục vụ truy xuất các phẩn tử ngẫy nhiên nhanh|- Linked list được sử dụng khi ta càn sử dụng để lưu trữ mảng linh hoạt về số lượng và có thể thêm xóa các phần tử vào vị trí bất kì dễ dàng|

## Ví Dụ và Kết Quả của Linked List

__Ví dụ:__
```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define NODE_EMPTY -1

typedef struct Node
{
    int data;
    struct Node *next;
} Node;


Node *createNode(int value); 
void push_back(Node** array, int value);    // them 1 node vao phia sau
void push_front(Node **array, int value);   // them 1 node vao phia truoc
void insert(Node **array, int value, int pos); // them 1 node vao mot vi tri bat ky

void pop_back(Node **array);                // xoa node cuoi cung
void pop_front(Node **array);               // xoa node dau tien
void erase(Node **array, int pos);          // xoa 1 node tai mot vi tri bat ky

int front(Node *array);                     // lay gia tri cua node dau tien
int back(Node *array);                      // lay gia tri cua node cuoi cung
int get(Node *array, int pos);              // lay gia tri cua node tai mot vi tri bat ky

int size(Node *array);                      // lay kich thuoc cua list
bool empty(Node *array);                    // kiem tra list co rong hay khong
void clear(Node **head);                    // xóa toàn bộ node
void printList(Node *array);                // in ra danh sach cua list

int main()
{
    Node* arr = NULL;
    push_back(&arr, 2);
    push_back(&arr, 7);
    push_back(&arr, 4);
    push_front(&arr, 5);
    push_front(&arr, 3);

    printList(arr);

    printf("Value test %d: %d\n", 2, get(arr, 2));
    printf("Value test %d: %d\n", 0, get(arr, 0));
    printf("Value test %d: %d\n", 4, get(arr, 4));
    printf("Size of list: %d\n", size(arr));

    pop_back(&arr);
    pop_front(&arr);

    printList(arr);
    printf("Value test front: %d\n", front(arr));
    printf("Value test back: %d\n", back(arr));

    insert(&arr, 10, 2);
    printList(arr);

    erase(&arr, 1);
    printList(arr);

    clear(&arr);
    printList(arr);

	return 0;
}

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void push_back(Node** array, int value)
{
    if(empty(*array))
    {
        printf("Push %d to list\n", value);
        *array = createNode(value);
    }
    else{
        printf("Push %d to back\n", value);
        Node *p = *array;
        while(p->next != NULL) p = p->next;
        p->next = createNode(value);
    }
}

void push_front(Node **array, int value) // them 1 node vao phia truoc
{
    if(empty(*array))
    {
        printf("Push %d to list\n", value);
        *array = createNode(value);
    }
    else{
        printf("Push %d to front\n", value);
        Node *p = createNode(value);
        p->next = *array;
        *array = p;
    }
}

void pop_back(Node **array)
{
    if(empty(*array)) return;
    Node *p = *array;
    if(p->next == NULL)
    {
        free(p);
        *array = NULL;
    }
    else{

        while(p->next->next != NULL) p = p->next;
        printf("Pop back value: %d\n", p->next->data);
        free(p->next);
        p->next = NULL;
    }
}


void pop_front(Node **array) // xoa node dau tien
{
    if(empty(*array)) return;
    Node *p = *array;
    *array = p->next;
    printf("Pop front value: %d\n", p->data);
    free(p);
}


int front(Node *array) // lay gia tri cua node dau tien
{
    if(empty(array)) return NODE_EMPTY;
    return array->data;
}


int back(Node *array) // lay gia tri cua node cuoi cung
{

    if(empty(array)) return NODE_EMPTY;
    Node *p = array;
    while(p->next != NULL) p = p->next;
    return p->data;
}


void insert(Node **array, int value, int pos) // them 1 node vao mot vi tri bat ky
{
    if(pos == 0) push_front(array, value);
    else{
        Node *p = *array;
        int count = 0;
        while(count < pos - 1 && p->next != NULL)
        {
            p = p->next;
            count++;
        }
        if(count == pos - 1)
        {
            printf("Insert %d to pos %d\n", value, pos);
            Node *newNode = createNode(value);
            newNode->next = p->next;
            p->next = newNode;
        }
    }
}

void erase(Node **array, int pos) // xoa 1 node tai mot vi tri bat ky
{
    if(pos == 0) pop_front(array);
    else{
        Node *p = *array;
        int count = 0;
        while(count < pos - 1 && p->next != NULL)
        {
            p = p->next;
            count++;
        }
        if(count == pos - 1)
        {
            Node *del = p->next;
            p->next = p->next->next;
            printf("Erase value %d at pos %d\n", del->data, pos);
            free(del);
        }
    }
}

int size(Node *array) // lay kich thuoc cua list
{
    int count = 0;
    Node *p = array;
    while(p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

int get(Node *array, int pos) // lay gia tri cua node tai mot vi tri bat ky
{
    if(empty(array)) return NODE_EMPTY;
    Node *p = array;
    int count = 0;
    while(count < pos && p != NULL)
    {
        p = p->next;
        count++;
    }
    if(count == pos) return p->data;
    printf("Error: List has less element\n");
    return 0;
} 


bool empty(Node *array) // kiem tra list co rong hay khong
{
    return array == NULL;
}

void clear(Node **head) // xóa toàn bộ node
{
    printf("Delete list\n");
    Node *p = *head;
    while(p != NULL)
    {
        *head = p->next;
        free(p);
        p = *head;
    }
}

void printList(Node *array)
{
    Node *p = array;
    printf("\nList:\t");
    if(p == NULL) printf("Empty");
    else{
        printf("Stt\tValue\n");
        int count = 0;
        while(p != NULL)
        {
            printf(" \t%d\t%d\n", count, p->data);
            p = p->next;
            count++;
        }
        printf("\n");
    }
    
}
```

__Kết quả:__
```c
Push 2 to list
Push 7 to back
Push 4 to back
Push 5 to front
Push 3 to front

List:   Stt     Value
        0       3
        1       5
        2       2
        3       7
        4       4

Value test 2: 2
Value test 0: 3
Value test 4: 4
Size of list: 5
Pop back value: 4
Pop front value: 3

List:   Stt     Value
        0       5
        1       2
        2       7

Value test front: 5
Value test back: 7
Insert 10 to pos 2

List:   Stt     Value
        0       5
        2       10
        3       7

Erase value 2 at pos 1

List:   Stt     Value
        0       5
        1       10
        2       7

Delete list

List:   Empty
```
