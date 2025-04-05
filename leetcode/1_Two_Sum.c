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

#if defined(hash)
//Runtime 2 ms Beats 94.81%
//Memory 9.21 MB Beats 10.24%

typedef struct hash_map_entry {
    int idx;        // idx of nums
    int val;        // nums[idx]
    struct hash_map_entry *next;
} HashMapEntry;

typedef struct {
    HashMapEntry **table;
    int size;
} HashMap;

HashMap *createHashMap(int size)
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->size = size;
    map->table = (HashMapEntry **)malloc(sizeof(HashMapEntry *)*size);
    for (int i=0; i<size; i++) {
        map->table[i] = NULL;
    }
    return map;
}

void freeHashMap(HashMap *map)
{
    HashMapEntry *entry, *next;
    for (int i=0; i<map->size; i++) {
        entry = map->table[i];
        while (entry) {
            next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(map);
}

HashMapEntry *createEntry(int idx, int val)
{
    HashMapEntry *ret = (HashMapEntry *)malloc(sizeof(HashMapEntry));
    ret->idx = idx;
    ret->val = val;
    ret->next = NULL;
    return ret;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    // init hashmap
    int table_size = 100;       // this value is important for memory cost
    HashMap *map = createHashMap(table_size);
    HashMapEntry *entry;
    int val, complement, key;
    int *ret = NULL;

    for (int i=0; i<numsSize; i++) {
        val = nums[i];
        complement = target - val;
        key = abs(complement) % table_size;
        entry = map->table[key];

        // find out such entry in table
        while (entry) {
            if (entry->val == complement) {
                ret = (int *)malloc(sizeof(int)*2);
                ret[0] = entry->idx;
                ret[1] = i;
                *returnSize = 2;
                goto out;
            } else {
                entry = entry->next;
            }
        }

        // if not finding, create new entry and insert to table
        entry = createEntry(i, val);
        key = abs(val) % table_size;
        entry->next = map->table[key];
        map->table[key] = entry;
    }

out:
    freeHashMap(map);
    return ret;
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
