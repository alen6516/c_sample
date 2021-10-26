/***
 File Name: ring_queue.c
 Author: alen6516
 Created Time: 2019-07-01
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
//gcc 5.4.0

#define LEN 10
#define TEST_NODE_NUM 30

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
    q->tail = (q->tail+1) % LEN;

    if (q->tail == q->head) {
        q->full = true;
    }

    return node;
}

void* pop (q_t *q)
{
    if (q->head == q->tail && !q->full ) {
        printf("empty\n");
        return NULL;
    }
    
    void* ret = q->queue[q->head];
    q->head = (q->head+1) % LEN;
    if (q->full) {
        q->full = false;
    }
    return ret;
}

int main ()
{
    q_t *q = init();
    if (!q) {
        printf("out of mem\n");
        return -1;
    }

    int push_arr[TEST_NODE_NUM];
    int pop_arr[TEST_NODE_NUM];

    srand(time(NULL));

    n_t *node;
    int i, j;
    i = j = 0;
    while(j != TEST_NODE_NUM) {
        if (rand() % 3 == 0 && i < TEST_NODE_NUM) {
            node = (n_t*)malloc(sizeof(n_t));
            node->val = rand() % 100;
            if (push(q, node)) {
                push_arr[i++] = node->val;
            } else {
                free(node);
            }
        } else {
            node = pop(q);
            if (node) {
                pop_arr[j++] = node->val;
                free(node);
            }
        }
    }

    printf("push_arr = [");
    for (int i=0; i<TEST_NODE_NUM; i++) {
        printf("%d, ", push_arr[i]);       
    }
    printf("]\n");

    printf("pop_arr = [");
    for (int i=0; i<TEST_NODE_NUM; i++) {
        printf("%d, ", pop_arr[i]);       
    }
    printf("]\n");
}
