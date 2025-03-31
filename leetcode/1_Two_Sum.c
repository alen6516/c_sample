/**
 * Description
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#ifdef array

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    int arr[10000] = {{-1}};
    int *ret = malloc(sizeof(int)*2);
    int val, complement;

    for (int i=0; i<numsSize; i++) {
        val = nums[i];
        complement = target-val;
        if (arr[complement] != -1) {
            ret[0] = arr[complement];
            ret[1] = i;
            *returnSize = 2;
            return ret;
        } else {
            arr[val] = i;
        }
    }
    return NULL;
}

#elif def hash
typedef struct hash_map_entry {
    int key;
    int val;
    struct hash_map_entry *next;
} HashMapEntry;

typedef struct {
    HashMapEntry *table;
    int size;
} HashMap;

HashMap *createHashMap(int size)
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->size = size;
    map->table = (HashMapEntry *)malloc(sizeof(HashMapEntry)*size);
    for (int i=0; i<size; i++) {
        map->table[i].key = -1;
        map->table[i].next = NULL;
    }
    return map;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    
    // init hashmap
    HashMap *map = createHashMap(numsSize*2);

    for (int i=0; i<numsSize; i++) {
        key = nums[i] % numsSize;
        if (map->table[key].key 
    }
}

#else
// Runtime 101 ms Beats 54.79%
// Memory 8.58 MB Beats 92.56%

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
 
    int *ret = (int*) malloc(sizeof(int)*2);

    for (int i=0; i<numsSize-1; i++) {
        for (int j=i+1; j<numsSize; j++) {
            if (nums[i]+nums[j] == target) {
                ret[0] = i;
                ret[1] = j;
                goto out;
            }
        }
    }

out:
    *returnSize = 2;
    return ret;
}
#endif
