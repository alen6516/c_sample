#ifndef MEMD_QUEUE_H
#define MEMD_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define QUEUE_SIZE 10

/*
 * 1. use de_head, en_head flag
 * 2. waste one space of arr
 */

struct queue_t {
    void* queue_arr[QUEUE_SIZE];
    int de_head;
    int en_head;
};


struct queue_t* init_queue()
{
    struct queue_t* ret;
    ret = (struct queue_t*) malloc(sizeof(struct queue_t));
    if (NULL != ret) {
        bzero(ret, sizeof(struct queue_t));
    }
    return ret;
}

//multiple enqueue
int en_queue(void* node, struct queue_t* queue)
{
    int curr_en_head;
    int next_en_head;

    do {
        curr_en_head = queue->en_head;
        next_en_head = (curr_en_head+1) % SIZE;
        if (next_en_head == queue->de_head) {
            // full
            return 1;
        }
    } while (!__sync_bool_compare_and_swap(&(queue->en_head), curr_en_head, next_en_head));

    queue->queue_arr[curr_en_head] = node;
    return 0;
}


// multiple dequeue
void* de_queue(struct queue_t* queue)
{
    // contest, take and move de_head
    int curr_de_head;
    int next_de_head;
    do {
        curr_de_head = queue->de_head;
        next_de_head = (curr_de_head+1) % SIZE;
        if (curr_de_head == queue->en_head) {
            // empty
            return NULL;
        }
    } while (!__sync_bool_compare_and_swap(&(queue->de_head), curr_de_head, next_de_head));
    
    return queue->queue_arr[curr_de_head];
}

#endif
