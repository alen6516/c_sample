#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef struct {
    int len;
    int size;
    int *arr;
} Stack;



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
    if (obj->in_stack.size == 0) {
        obj->in_stack.arr = (int *)malloc(sizeof(int)*SIZE);
        obj->in_stack.size = SIZE;
        obj->in_stack.len = 0;
    }

    if (obj->in_stack.len == obj->in_stack.size) {  // if full, either enlarge or move elements to out_stack
        int *arr = (int*) malloc(sizeof(int)*obj->in_stack.size*2);
        memcpy(arr, obj->in_stack.arr, sizeof(int)*obj->in_stack.size);
        free(obj->in_stack.arr);
        obj->in_stack.arr = arr;
        obj->in_stack.size *= 2;
    }

    obj->in_stack.arr[obj->in_stack.len++] = x;
}

int myQueuePop(MyQueue* obj) {

    if (0 == obj->out_stack.len) {
        while (obj->in_stack.len)
            obj->out_stack.arr[obj->out_stack.len ++] = obj->in_stack.arr[obj->in_stack.len --];
    }

    return obj->out_stack.arr[obj->out_stack->len--];
}

int myQueuePeek(MyQueue* obj) {

    if (0 == obj->out_stack.len) {
        while (obj->in_stack.len)
            obj->out_stack.arr[obj->out_stack.len ++] = obj->in_stack.arr[obj->in_stack.len --];
    }

    return obj->out_stack.arr[obj->out_stack->len];
}

bool myQueueEmpty(MyQueue* obj) {
    return !(obj->in_stack.len | obj->out_stack.len);
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
