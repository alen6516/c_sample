#ifndef RING_QUEUE_H
#define RING_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10


struct node_t {
    int val;
};


struct queue_t {

    void* queue_arr[SIZE];
    int de_head;
    int en_head;
    int en_tail;

};

struct queue_t* queue;

int init_queue(struct queue_t* queue) {
    queue = (struct queue_t*) malloc(sizeof(struct queue_t));
    bzero(queue, sizeof(struct queue_t));
    return 0;
}

// muti enqueue
int en_queue(void* node, struct queue_t* queue) {
    int tmp_en_head;
    int tmp_en_head_next;

    do {
        tmp_en_head = queue->en_head;
        tmp_en_head_next = (tmp_en_head+1) % SIZE;
    
    } while ( !__sync_bool_compare_and_swap(&(queue->en_head), tmp_en_head, tmp_en_head_next));

    queue->queue_arr[tmp_en_head]
}




#endif
