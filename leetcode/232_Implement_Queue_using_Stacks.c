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

    if (obj->in_stack.len == obj->in_stack.size) {
        int *arr = (int*) malloc(sizeof(int)*obj->in_stack.size*2);
        memcpy(arr, obj->in_stack.arr, sizeof(int)*obj->in_stack.size);
        free(obj->in_stack.arr);
        obj->in_stack.arr = arr;
        obj->in_stack.size *= 2;
    }

    obj->in_stack.arr[obj->in_stack.len++] = x;
}

int myQueuePop(MyQueue* obj) {

}

int myQueuePeek(MyQueue* obj) {

}

bool myQueueEmpty(MyQueue* obj) {

}

void myQueueFree(MyQueue* obj) {

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
