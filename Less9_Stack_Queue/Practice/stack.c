#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_EMPTY -1

typedef struct {
    int *item;
    int top;
    int size;
} Stack;

#define PRINT_POP(stack)    if(peak(*stack) != STACK_EMPTY) printf("Element pop: %d\n", pop(stack));
#define PRINT_PEAK(stack)   if(peak(stack) != STACK_EMPTY) printf("Element peak: %d\n", peak(stack));



// Khởi tạo
int init_Stack(Stack *stack, int newSize)
{
    stack->size = newSize;
    stack->item = (int *)malloc(newSize * sizeof(int));
    stack->top = STACK_EMPTY;
}

// Kiểm tra rỗng
bool isEmpty(Stack stack)
{
    return stack.top == STACK_EMPTY;
}

// Kiểm tra đầy
bool isFull(Stack stack)
{
    return stack.top == stack.size - 1;
}

// Thêm phẩn tử
void push(Stack *stack, int data)
{
    if(isFull(*stack))
    {
        printf("Stack Full!\n");
    }else{
        stack->item[++stack->top] = data;
    }
}

// Xóa phần tử
int pop(Stack *stack){
    int data;
    if(isEmpty(*stack))
    {
        printf("Stack Empty!\n");
        return STACK_EMPTY;
    }else{
          data = stack->item[stack->top];
          stack->item[stack->top--] = 0;
          return data;
    }
}

// Đọc phần tử
int peak(Stack stack){
    if(isEmpty(stack))
    {
        printf("Stack Empty!\n");
        return STACK_EMPTY;
    }else{
          return stack.item[stack.top];
    } 
}

void displayStack(Stack stack)
{
    if(stack.top < 0){
        printf("\n");
        printf("Stack List Empty!\n");
        printf("\n");
    }else{
        printf("\n");
        printf("Display element:\n");
        for(int i = stack.top; i >= 0 ; i--){
            printf("Element %d: %d\n", i, stack.item[i]);
        }
        printf("\n");
    }
}

int main(){

    Stack stack1;
    init_Stack(&stack1, 6);

    push(&stack1, 1);
    push(&stack1, 2);
    push(&stack1, 3);
    push(&stack1, 4);
    push(&stack1, 5);

    displayStack(stack1);

    // printf("Element peak: %d\n", peak(stack1));
    PRINT_PEAK(stack1);
    // printf("Element pop: %d\n", pop(&stack1));
    PRINT_POP(&stack1);


    displayStack(stack1);

    printf("Element pop: %d\n", pop(&stack1));

    displayStack(stack1);

    push(&stack1, 43);
    push(&stack1, 33);
    push(&stack1, 85);
    push(&stack1, 26);

    displayStack(stack1);

    // printf("Element pop: %d\n", pop(&stack1));
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);
    PRINT_POP(&stack1);

    displayStack(stack1);

    return 0;
}