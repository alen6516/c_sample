#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 10

typedef struct {
    int len;
    int size;
    int *arr;
} Stack;


static int stack_pop(Stack *stack)
{
    return stack->arr[--stack->len];
}

static void stack_push(Stack *stack, int val)
{
    if (stack->size == 0) {                     // init stack
        stack->arr = (int*) malloc(sizeof(int)*SIZE);
        stack->len = 0;
        stack->size = SIZE;
    } else if (stack->len == stack->size) {     // full, enlarge the stack
        int *arr = (int*) malloc(sizeof(int)*stack->size*2);
        memcpy(arr, stack->arr, sizeof(int)*stack->size);
        free(stack->arr);
        stack->arr = arr;
        stack->size *= 2;
    }

    stack->arr[stack->len++] = val;
}

typedef struct {
    Stack in_stack;
    Stack out_stack;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue *ret;
    ret = (MyQueue *) malloc(sizeof(MyQueue));
    ret->in_stack.size = 0;
    ret->out_stack.size = 0;
    return ret;
}

void myQueuePush(MyQueue* obj, int x) {
    Stack *in_stack = &obj->in_stack;
    stack_push(in_stack, x);
}

int myQueuePop(MyQueue* obj) {

    Stack *in_stack = &obj->in_stack;
    Stack *out_stack = &obj->out_stack;

    if (0 == out_stack->size || 0 == out_stack->len) {
        while (in_stack->len) {
            stack_push(out_stack, stack_pop(in_stack));
        }
    }

    return obj->out_stack.arr[--obj->out_stack.len];
}

int myQueuePeek(MyQueue* obj) {

    if (0 == obj->out_stack.size || 0 == obj->out_stack.len) {
        while (obj->in_stack.len) {
            stack_push(&obj->out_stack, stack_pop(&obj->in_stack));
        }
    }

    return obj->out_stack.arr[obj->out_stack.len-1];
}

bool myQueueEmpty(MyQueue* obj) {
    return !(obj->in_stack.size | obj->out_stack.size) || !(obj->in_stack.len | obj->out_stack.len);
}

void myQueueFree(MyQueue* obj) {

    if (obj->in_stack.size) free(obj->in_stack.arr);
    if (obj->out_stack.size) free(obj->out_stack.arr);
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/

int main()
{
    MyQueue* obj = myQueueCreate();
    printf("%d %d\n", obj->in_stack.size, obj->in_stack.size);
    myQueuePush(obj, 1);
    myQueuePush(obj, 2);
    int p = myQueuePeek(obj);
    printf("peek: %d\n", p);
    p = myQueuePop(obj);
    printf("pop: %d\n", p);
    p = myQueuePeek(obj);
    printf("peek: %d\n", p);
    p = myQueuePop(obj);
    printf("pop: %d\n", p);
}
