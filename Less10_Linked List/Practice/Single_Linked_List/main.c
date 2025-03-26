#include "LinkedList.h"

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
