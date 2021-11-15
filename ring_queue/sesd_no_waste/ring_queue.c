/**
 * Try to implement a one-producer-one-consumer ring_queue
 * without lock and without wasting a unit in array.
 * Not sure if success or not.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
//gcc 5.4.0

#include "util.h"

typedef struct queue {
    void* queue[QUEUE_LEN];
    bool is_full;
    bool is_empty;
    u32 head, tail;
} q_t;


static q_t* init()
{
    q_t *q = (q_t *)malloc(sizeof(q_t));
    if (!q) return NULL;
    memset(q, 0, sizeof(q_t));
    return q;
}

static void* push (q_t *q, void *node)
{
    if (q->is_full) {
        //printf("full\n");
        return NULL;
    }
   
    q->queue[q->tail] = node;

    int new_tail = (q->tail+1) % QUEUE_LEN;
    if (new_tail == q->head) {
        q->is_full = true;
        if (new_tail != q->head && q->is_full) {
            q->is_full = false;    // prevent from block myself
        }
    }
    q->tail = new_tail;

    if (q->is_empty) {
        q->is_empty = false;
    }

    return node;
}

static void* pop (q_t *q)
{
    if (q->is_empty) {
        //printf("empty\n");
        return NULL;
    }
    
    void* ret = q->queue[q->head];
    int new_head = (q->head+1) % QUEUE_LEN;
    if (new_head == q->tail) {
        q->is_empty = true;
        if (new_head != q->tail && q->is_empty) {
            q->is_empty = false;   // prevent from block myself
        }
    }
    q->head = new_head;

    if (q->is_full) {
        q->is_full = false;
    }
    return ret;
}


static q_t *q;
static int push_arr[TEST_NODE_NUM];
static int pop_arr[TEST_NODE_NUM];
static int push_sum;
static int pop_sum;

static void *pusher(void *arg)
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
            push_sum += node->val;
        }
        count ++;
    }

    printf("pusher push %d node and use %d count\n", i, count);
}


static void *poper(void *arg)
{
    int i, count;
    i = count = 0;
    n_t *node;

    while(i < TEST_NODE_NUM && count < TRIE_COUNT) {
        node = pop(q);
        if (node) {
            pop_arr[i++] = node->val;
            pop_sum += node->val;
            free(node);
        }
        count ++;
    }

    printf("poper pop %d node and use %d try_count\n", i, count);
}

void
//test_no_lock_ring_queue()
main()
{
    q = init();
    if (!q) {
        printf("out of mem\n");
        return;
    }

    srand(time(NULL));

    printf("test_no_lock_ring_queue: =============\n");

    pthread_t p1, p2;   
    pthread_create(&p1, NULL, pusher, NULL);    // one producer
    pthread_create(&p2, NULL, poper, NULL);     // one consumer

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("push_arr = [");
    show_arr(push_arr, TEST_NODE_NUM);
    printf("]\n");
    printf("push_sum = %d\n", push_sum);
    
    printf("pop_arr = [");
    show_arr(pop_arr, TEST_NODE_NUM);
    printf("]\n");
    printf("pop_sum = %d\n", pop_sum);
}
