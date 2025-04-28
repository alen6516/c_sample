#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 31

typedef struct _entry {
    int val;
    struct _entry *next;
} Entry;

void map_free(Entry **map)
{
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

Entry **map_create(int size)
{
    Entry **map = (Entry**)malloc(sizeof(Entry*)*SIZE);
    Entry *map[SIZE];
    memset(map, 0, sizeof);
    return map;
}

// calculate
int get_val(int n)
{
    int ret = 0;
    while (n) {
        ret += pow((n%10), 2);
        n /= 10;
    }
    return ret;
}

bool isHappy(int n)
{
    // hash table to mark if a number is happy
    Entry **map = map_create(SIZE);
    bool ret;
    int key, val;
    Entry *entry;
    while (1) {
        val = get_val(n);
        if (val == 1) {
            ret = true;
            goto out;
        } else if (val < 10) {
            ret = false;
            goto out;
        }

        // insert to hash table
        key = val % SIZE;
        entry = map[key];
        while (entry) {
            if (entry->val == val) { // result in a loop
                ret = false;
                goto out;
            }
            entry = entry->next;
        }

        // insert new entry
        entry = malloc(sizeof(Entry));
        entry->val = val;
        entry->next = map[key];
        map[key] = entry;
    }

out:
    map_free(map);
    return ret;
}
