#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "util.h"

#define LEN 5
#define TEST_NODE_NUM 30
#define TRIE_COUNT 1000

extern void test_no_lock_ring_queue();
//extern void test_lock_ring_queue();

int main()
{
    test_no_lock_ring_queue();
    //test_lock_ring_queue();
}
