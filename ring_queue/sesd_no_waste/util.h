#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef struct node {
    u32 val;
} n_t;

#define QUEUE_LEN 5
#define TEST_NODE_NUM 30
#define TRIE_COUNT 1000

static void
show_arr(int *arr, int len)
{
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);       
    }
}

#endif
