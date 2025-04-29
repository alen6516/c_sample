#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Runtime 0 ms Beats 100.00%
//Memory 7.89 MB Beats 29.39%

#define SIZE 9      // this size affect performance and memory usage

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
    memset(map, 0, sizeof(Entry*)*SIZE);
    return map;
}

// calculate
int get_val(int n)
{
    int ret = 0;
    while (n) {
        ret += (n%10)*(n%10);
        n /= 10;
    }
    printf("%d\n", ret);
    return ret;
}

bool isHappy(int n)
{
    // hash table to mark if a number is happy
    Entry **map = map_create(SIZE);
    bool ret;
    int key;
    Entry *entry;
    while (1) {
        n = get_val(n);
        if (n == 1) {
            ret = true;
            goto out;
        }

        // check if val already in hash table
        key = n % SIZE;
        entry = map[key];
        while (entry) {
            if (entry->val == n) { // result in a loop
                ret = false;
                goto out;
            }
            entry = entry->next;
        }

        // insert new entry
        entry = malloc(sizeof(Entry));
        entry->val = n;
        entry->next = map[key];
        map[key] = entry;
    }

out:
    map_free(map);
    return ret;
}

int main()
{
    int in = 19;
    printf("%s\n", isHappy(in) ? "true": "false");
}
