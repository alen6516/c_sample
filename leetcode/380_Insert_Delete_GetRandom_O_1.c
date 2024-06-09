#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#define SIZE 10

typedef struct {
    int arr_len;
    int curr_len;
    int *arr;
} RandomizedSet;


RandomizedSet* randomizedSetCreate() {
    RandomizedSet *ret;
    ret = (RandomizedSet*) malloc(sizeof(RandomizedSet));
    ret->arr = (int*) malloc(sizeof(int)*SIZE);
    ret->arr_len = SIZE;
    ret->curr_len = 0;
    return ret;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    if (obj->curr_len == obj->arr_len) {
        int *arr = malloc(sizeof(int)*(obj->arr_len + SIZE));
        memcpy(arr, obj->arr, sizeof(int)*obj->arr_len);
        free(obj->arr);
        obj->arr = arr;
        obj->arr_len = obj->arr_len + SIZE;
    }
    obj->arr[obj->curr_len++] = val;
    return 1;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    for (int i=0; i < obj->arr_len; i++) {
        if (val == obj->arr[i]) {
            obj->arr[i] = obj->arr[obj->arr_len-1];
            obj->arr_len --;
            return 1;
        }
    }
    return 0;
}

int randomizedSetGetRandom(RandomizedSet* obj) {

}

void randomizedSetFree(RandomizedSet* obj) {
    if (obj) {
        if (obj->arr)
            free(obj->arr);
        free(obj);
    }
}

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);

 * bool param_2 = randomizedSetRemove(obj, val);

 * int param_3 = randomizedSetGetRandom(obj);

 * randomizedSetFree(obj);
*/

int main()
{
    
}
