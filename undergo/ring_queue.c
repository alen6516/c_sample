/**
 * Try to implement a one-producer-one-consumer ring_queue
 * without lock and without wasting a unit in array.
 * Not sure if success or not.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
//gcc 5.4.0

#define LEN 5
#define TEST_NODE_NUM 30
#define TRIE_COUNT 1000

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef struct node {
    u32 val;
} n_t;

typedef struct queue {
    void* queue[LEN];
    bool full;
    bool empty;
    u32 head, tail;
} q_t;


q_t* init()
{
    q_t *q = (q_t *)malloc(sizeof(q_t));
    if (!q) return NULL;
    memset(q, 0, sizeof(q_t));
    return q;
}

void* push (q_t *q, void *node)
{
    if (q->full) {
        printf("full\n");
        return NULL;
    }
   
    q->queue[q->tail] = node;

    int new_tail = (q->tail+1) % LEN;
    if (new_tail == q->head) {
        q->full = true;
        if (new_tail != q->head && q->full) {
            q->full = false;    // prevent from block myself
        }
    }
    q->tail = new_tail;

    if (q->empty) {
        q->empty = false;
    }

    return node;
}

void* pop (q_t *q)
{
    if (q->empty) {
        printf("empty\n");
        return NULL;
    }
    
    void* ret = q->queue[q->head];
    int new_head = (q->head+1) % LEN;
    if (new_head == q->tail) {
        q->empty = true;
        if (new_head != q->tail && q->empty) {
            q->empty = false;   // prevent from block myself
        }
    }
    q->head = new_head;

    if (q->full) {
        q->full = false;
    }
    return ret;
}


q_t *q;
int push_arr[TEST_NODE_NUM];
int pop_arr[TEST_NODE_NUM];

void *pusher(void *arg)
{
    int i, count;
    i = count = 0;
    n_t *node;
    srand(time(NULL));

    while(i < TEST_NODE_NUM && count < TRIE_COUNT) {
        node = (n_t*)malloc(sizeof(n_t));
        node->val = rand() % 100;
        if (push(q, node)) {
            push_arr[i++] = node->val;
        }
        count ++;
    }

    printf("pusher push %d node and use %d count\n", i, count);
    //printf("push_arr = [");
    //for (int j=0; j<i; j++) {
    //    printf("%d, ", push_arr[j]);       
    //}
    //printf("]\n");
}


void *poper(void *arg)
{
    int i, count;
    i = count = 0;
    n_t *node;

    while(i < TEST_NODE_NUM && count < TRIE_COUNT) {
        node = pop(q);
        if (node) {
            pop_arr[i++] = node->val;
            free(node);
        }
        count ++;
    }

    printf("poper pop %d node and use %d count\n", i, count);
    //printf("pop_arr = [");
    //for (int j=0; j<i; j++) {
    //    printf("%d, ", pop_arr[j]);       
    //}
    //printf("]\n");
}

int main ()
{
    q = init();
    if (!q) {
        printf("out of mem\n");
        return -1;
    }

    srand(time(NULL));

    pthread_t p1, p2;   
    pthread_create(&p1, NULL, pusher, NULL);    // one producer
    pthread_create(&p2, NULL, poper, NULL);     // one consumer

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("pop_arr = [");
    for (int j=0; j<TEST_NODE_NUM; j++) {
        printf("%d, ", pop_arr[j]);       
    }
    printf("]\n");
    
    printf("pop_arr = [");
    for (int j=0; j<TEST_NODE_NUM; j++) {
        printf("%d, ", pop_arr[j]);       
    }
    printf("]\n");
}
