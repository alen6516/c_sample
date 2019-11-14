#ifndef SEMD_QUEUE_H
#define SEMD_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10


/*
 * 1. use de_head, en_head flag
 * 2. waste one space of arr
 */


struct queue_t {

    void* queue_arr[SIZE];
    int de_head;
    int en_head;
};


struct queue_t* init_queue() {
    struct queue_t* ret;
    ret = (struct queue_t*) malloc(sizeof(struct queue_t));
    if (ret != NULL) {
        bzero(ret, sizeof(struct queue_t));
    }
    return ret;
}

// single enqueue
int en_queue(void* node, struct queue_t* queue) {
    int tmp = (queue->en_head+1) % SIZE;
    if (tmp == queue->de_head) {
        // full (actually left 1 space empty)
        return 1;
    } else {
        // put and move en_head
        int curr_en_head = queue->en_head;
        queue->queue_arr[curr_en_head] = node;
        queue->en_head = (curr_en_head+1) % SIZE;
    }
    return 0;
}


// multiple dequeue
void* de_queue(struct queue_t* queue) {
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
    } while(!__sync_bool_compare_and_swap(&(queue->de_head), curr_de_head, next_de_head));
    
    return queue->queue_arr[curr_de_head];
}


#endif
