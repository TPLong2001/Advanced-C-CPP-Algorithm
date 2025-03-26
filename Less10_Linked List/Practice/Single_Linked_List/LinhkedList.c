/***************************************************************************
 * @file    LinkedList.c
 * @brief   Định nghĩa các hàm thao tác với danh sách liên kết đơn (single linked list)
 * @details File này định nghĩa các hàm sử dụng thao tác với linked list bao gồm:
 *          khởi tạo node mới, thêm, xóa các node vào các vị trí khác nhau, 
 *          Đọc và hiển thị các node hoặc list.
 * @version 1.0
 * @date    2025-03-13
 * @author  LongTruong
 ***************************************************************************/

 /* ==================================================[ INCLUDE FILE ]====================================================*/
#include "LinkedList.h"

/* ==============================================[ FUNCTION INPLEMENTATION ]==============================================*/
/****************************************************************************
 * @brief   Khởi tạo Node.
 * @details Hàm này khởi tạo Node mới với giá trị được truyền vào.
 * @param   value   dữ liệu của node mới.
 * @return  Node * con trỏ trỏ đến node mới được khởi tạo.
 ***************************************************************************/
Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}


/****************************************************************************
 * @brief   Thêm phần tử vào cuối danh sách liên kết
 * @details Hàm này thêm phần tử vào cuối danh sách liên kết.
 *          Nếu danh sách rỗng thì tạo node mới và gán vào vị trí đầu tiên.
 *          Nếu danh sách không rỗng thì tìm vị trí cuối cùng và thêm node mới vào cuối.
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   value   dữ liệu của node mới.
 * @return  void
 ***************************************************************************/
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


/****************************************************************************
 * @brief   Thêm phần tử vào đầu danh sách liên kết
 * @details Hàm này thêm phần tử vào đầu danh sách liên kết.
 *          Nếu danh sách rỗng thì tạo node mới và gán vào vị trí đầu tiên.
 *          Nếu danh sách không rỗng thì tạo node mới và chèn vào vị trí đầu tiên của danh sách.
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   value   dữ liệu của node mới.
 * @return  void
 ***************************************************************************/
void push_front(Node **array, int value)
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


/****************************************************************************
 * @brief   Thêm phần tử vào vị trí nào đó trong danh sách liên kết
 * @details Hàm này thêm phần tử vào vị nào đó trong danh sách liên kết.
 *          Nếu vị trí thêm vào là 0 thì thêm vào đầu danh sách.
 *          Nếu không thì tìm vị trí cần thêm và thêm vào vị trí đó.
 *          Nếu vị trí cần thêm lớn hơn số phần tử trong danh sách thì không thêm.
 * @param   array   con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   value   dữ liệu của node mới.
 * @param   pos     vị trí cần thêm.
 * @return  void
 ***************************************************************************/
void insert(Node **array, int value, int pos)
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


/****************************************************************************
 * @brief   Xóa phần tử ở cuối danh sách liên kết
 * @details Hàm này xóaphần tử ở cuối danh sách liên kết.
 *          Nếu danh sách rỗng thì không làm gì cả.
 *          Nếu danh sách không rỗng thì tìm và xóa node cuối cùng.
 *          Sau khi xóa thì cập nhật lại node cuối cùng của danh sách.
 * @param   array   Con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @return  void
 ***************************************************************************/
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


/****************************************************************************
 * @brief   Xóa phần tử ở đầu danh sách liên kết
 * @details Hàm này xóa phần tử ở đầu danh sách liên kết.
 *          Nếu danh sách rỗng thì không làm gì cả.
 *          Nếu danh sách không rỗng thì xóa node đầu tiên.
 *          Sau khi xóa thì cập nhật lại node đầu tiên của danh sách.
 * @param   array   Con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @return  void
 ***************************************************************************/
void pop_front(Node **array) // xoa node dau tien
{
    if(empty(*array)) return;
    Node *p = *array;
    *array = p->next;
    printf("Pop front value: %d\n", p->data);
    free(p);
}


/****************************************************************************
 * @brief   Xóa phần tử ở vị trí nào đó trong danh sách liên kết
 * @details Hàm này xóa phần tử ở vị trí nào đó trong danh sách.
 *          Nếu vị trí xóa là 0 thì xóa node đầu tiên.
 *          Nếu không thì tìm và xóa node ở vị trí cần xóa.
 *          Nếu vị trí cần xóa lớn hơn số phần tử trong danh sách thì không xóa.
 * @param   array   Con trỏ bậc 2 trỏ đến vị trí đầu danh sách liên kết.
 * @param   pos     Vị trí cần xóa.
 * @return  void
 ***************************************************************************/
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


/***************************************************************************
 * @brief   Lấy giá trị của Node đầu tiên trong danh sách liên kết.
 * @param   array   Con trỏ trỏ đến đầu danh sách.
 * @return  int     Giá trị của phần tử đầu danh sách.
***************************************************************************/
int front(Node *array)
{
    if(empty(array)) return NODE_EMPTY;
    return array->data;
}


/***************************************************************************
 * @brief   Lấy giá trị của Node cuối cùng trong danh sách liên kết.
 * @param   array   Con trỏ trỏ đến đầu danh sách.
 * @return  int     Giá trị của phần tử cuối cùng danh sách.
***************************************************************************/
int back(Node *array)
{
    if(empty(array)) return NODE_EMPTY;
    Node *p = array;
    while(p->next != NULL) p = p->next;
    return p->data;
}


/***************************************************************************
 * @brief   Lấy giá trị của Node nào đó trong danh sách liên kết.
 * @param   array   Con trỏ trỏ đến đầu danh sách.
 * @param   pos     Vị trí cần lấy giá trị.
 * @return  int     Giá trị của phần tử cần lấy trong danh sách.
***************************************************************************/
int get(Node *array, int pos)
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


/***************************************************************************
 * @brief   Lấy kích thước của danh sách liên kết.
 * @param   array   Con trỏ trỏ đến đầu danh sách.
 * @return  int     Số lượng phần tử trong danh sách.
***************************************************************************/
int size(Node *array)
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




/***************************************************************************
 * @brief   Kiểm tra danh sách có rỗng không.
 * @param   array   Con trỏ trỏ đến đầu danh sách.
 * @return  true    Nếu danh sách rỗng.
 * @return  false   Nếu danh sách không rỗng.
 ***************************************************************************/
bool empty(Node *array) // kiem tra list co rong hay khong
{
    return array == NULL;
}


/****************************************************************************
 * @brief   Khởi tạo Hàng đợi.
 * @details Hàm này khởi tạo hàng đợi với kích thước cố định.
 *          Biến size truyền vào kích thước tối đa của hàng đợi.
 * @param   queue   con trỏ trỏ đến hàng đợi.
 * @param   size    kích thước tối đa của hàng đợi.
 * @return  void
 ***************************************************************************/
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


/****************************************************************************
 * @brief   Khởi tạo Hàng đợi.
 * @details Hàm này khởi tạo hàng đợi với kích thước cố định.
 *          Biến size truyền vào kích thước tối đa của hàng đợi.
 * @param   queue   con trỏ trỏ đến hàng đợi.
 * @param   size    kích thước tối đa của hàng đợi.
 * @return  void
 ***************************************************************************/
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