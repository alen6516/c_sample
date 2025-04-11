#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Runtime 32 ms Beats 84.03%
//Memory 24.14 MB Beats 7.02%
typedef struct _entry {
    int val;
    struct _entry *next;
} Entry;

Entry **createMap(int size)
{
    Entry **ret = (Entry **)malloc(sizeof(Entry*)*size);
    memset(ret, 0, sizeof(Entry*)*size);
    return ret;
}

void freeMap(Entry **map) {
    Entry *entry, *next;
    for (int i=0; i<SIZE; i++) {
        entry = map[i];
        while (entry) {
            next = entry->next;
            free(entry);
            entry = next;
        }
    }
}

// create hash table
// for each val, check if there is a duplicate in hash table entry
// if not, create entry and insert to hash table
bool containsDuplicate(int* nums, int numsSize)
{
    if (numsSize == 1) return false;
    bool ret = false;
    int size = numsSize/2;
    Entry **map = createMap(size);

    int key, val;
    Entry *entry;
    for (int i=0; i<numsSize; i++) {
        val = nums[i];
        key = abs(val) % size;
        entry = map[key];
        while (entry) {
            if (entry->val == val) {
                ret = true;
                goto out;
            } else
                entry = entry->next;
        }

        // if not found, insert this entry
        entry = (Entry *)malloc(sizeof(Entry));
        entry->val = val;
        entry->next = map[key];
        map[key] = entry;
    }

out:
    freeMap(map);
    return ret;
}
