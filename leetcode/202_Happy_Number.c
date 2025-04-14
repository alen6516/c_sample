#include <stdio.h>
#include <stdlib.h>

#define SIZE 31

typedef struct _entry {
    int val;
    struct _entry *next;
} Entry;

void map_free(Entry **map)
{
    
}

int get_val(int n)
{

}

bool isHappy(int n)
{
    Entry **map = (Entry**)malloc(sizeof(Entry*)*SIZE);
    Entry *map[SIZE];
    memset(map, 0, sizeof);
    
    int key, val;
    Entry *entry;
    while (1) {
        val = get_val(n);
        if (val == 1) return true;
        else if (val < 10) return false;
        key = val % SIZE;
        entry = map[key];
        while (entry) {
            if (entry->val == val) return false;    // result in a loop
            entry = entry->next;
        }

        // insert new entry
        entry = malloc(sizeof(Entry));
        entry->val = val;
        entry->next = map[key];
        map[key] = entry;
    }
}
