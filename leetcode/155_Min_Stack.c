#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    int min_idx;
    int size;
    int len;
    int *stack;
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
    if (obj->len) obj->len --;
}

// get the top element of the stack
int minStackTop(MinStack* obj) {
    return (obj->len) ? obj->stack[obj->len-1] : -1;
}

// retrieves the min element from the stack
int minStackGetMin(MinStack* obj) {
    if (obj->len == 0) return -1;

    int ret = obj->stack[obj->min_idx];
    if (obj->len-1 > obj->min_idx) {
        memmove(&obj->stack[obj->min_idx], &obj->stack[obj->min_idx+1], sizeof(int)*(obj->len-obj->min_idx-1));
    }
    obj->len --;

    // find new min
    int min_idx = 0;
    if (obj->len == 1) goto done;

    for (int i=1; i < obj->len; i++) {
        if (obj->stack[i] < obj->stack[min_idx])
            min_idx = i;
    }

done:
    obj->min_idx = min_idx;
    return ret;
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
