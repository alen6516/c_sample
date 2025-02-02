#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#define SIZE 3

// need to allocate struct and allocate array inside
typedef struct {
    int arr_len;
    int curr_len;
    int *arr;
} RandomizedSet;


RandomizedSet* randomizedSetCreate() {
    printf("\n***** To create Set\n");

    RandomizedSet *ret;
    ret = (RandomizedSet*) malloc(sizeof(RandomizedSet));
    if (!ret) return NULL;
    ret->arr = (int*) malloc(sizeof(int)*SIZE);
    if (!ret->arr) {
        free(ret);
        return NULL;
    }
    ret->arr_len = SIZE;
    ret->curr_len = 0;
    return ret;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    printf("\n***** To insert %d\n", val);

    int i;
    for (i = 0; i < obj->curr_len; i++) {
        if (obj->arr[i] == val) return 0;
    }

    if (obj->curr_len == obj->arr_len) {
        int *arr;
        while (!(arr = malloc(sizeof(int)*(obj->arr_len + SIZE))));
        memcpy(arr, obj->arr, sizeof(int)*obj->arr_len);
        free(obj->arr);
        obj->arr = arr;
        obj->arr_len = obj->arr_len + SIZE;
    }
    obj->arr[obj->curr_len++] = val;
    return 1;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    printf("\n***** To remove %d\n", val);

    for (int i=0; i < obj->arr_len; i++) {
        if (val == obj->arr[i]) {
            obj->arr[i] = obj->arr[obj->curr_len-1];
            obj->curr_len --;
            return 1;
        }
    }
    return 0;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    printf("\n***** To getRandom\n");

    srand(time(NULL));
    int i = rand() % obj->curr_len;
    printf("get %d\n", obj->arr[i]);
    return obj->arr[i];
}

void randomizedSetFree(RandomizedSet* obj) {
    if (!obj) return;

    if (obj->arr)
        free(obj->arr);
    free(obj);
}

void randomizedSetCheck(RandomizedSet *obj, int ret) {

    printf("operation %s, ", (ret) ? "success" : "failed");

    if (!obj) return;

    printf("[");
    for (int i=0; i<obj->curr_len; i++) {
        printf("%d, ", obj->arr[i]);
    }
    printf("]\n");
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
    
    RandomizedSet* obj;
    int ret;

    obj = randomizedSetCreate();
    randomizedSetCheck(obj, !!obj);

    ret = randomizedSetInsert(obj, 1);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetRemove(obj, 2);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetInsert(obj, 2);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetGetRandom(obj);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetRemove(obj, 1);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetInsert(obj, 2);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetGetRandom(obj);
    randomizedSetCheck(obj, ret);





    ret = randomizedSetInsert(obj, 3);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetInsert(obj, 4);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetInsert(obj, 5);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetInsert(obj, 6);
    randomizedSetCheck(obj, ret);

    ret = randomizedSetInsert(obj, 7);
    randomizedSetCheck(obj, ret);
}
