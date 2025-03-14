// Runtime 0 ms Beats 100.00%
// Memory 18.49 MB Beats 96.11%


#include <stdlib.h>
#include <string.h>

#define SIZE 100    // adjusting this number can result in different performance

typedef struct {
    int min_idx;    // idx of the min element
    int size;       // size of stack
    int len;        // current len of stack
    int *stack;     // array
} MinStack;

MinStack* minStackCreate() {
    MinStack *ret = (MinStack*)malloc(sizeof(MinStack));
    ret->stack = (int*) malloc(sizeof(int)*SIZE);
    ret->len = 0;
    ret->size = SIZE;
    return ret;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->len == obj->size) { // if full
        int *new_stack = (int*) malloc(sizeof(int)*obj->size*2);
        memcpy(new_stack, obj->stack, sizeof(int)*obj->size);
        obj->size = obj->size*2;
        free(obj->stack);
        obj->stack = new_stack;
    }

    obj->stack[obj->len++] = val;
    if (obj->len == 1 || val < obj->stack[obj->min_idx]) {  // update min
        obj->min_idx = obj->len-1;
    }
}

// remove the top element from the stack
void minStackPop(MinStack* obj) {
    obj->len--;
    if (obj->min_idx == obj->len) {   // if min is the top one, find new min
        obj->min_idx = 0;
        for (int i=1; i < obj->len; i++) {
            if (obj->stack[i] < obj->stack[obj->min_idx])
                obj->min_idx = i;
        }
    }
}

// get the top element of the stack
int minStackTop(MinStack* obj) {
    return obj->stack[obj->len-1];
}

// retrieves the min element from the stack
int minStackGetMin(MinStack* obj) {
    return obj->stack[obj->min_idx];
}

void minStackFree(MinStack* obj) {
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
