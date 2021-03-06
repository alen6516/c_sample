/***
 File Name: ring_queue.c
 Author: alen6516
 Created Time: 2019-07-01
***/

#ifndef RING_QUEUE_H
#define RING_QUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//gcc 5.4.0

#define LEN 5

typedef struct node {
    int val;
} n_t;


typedef struct queue {
    void* queue[LEN];
    bool full;
    
    // boundary of the ring queue
    int a;
    int z;

    // current index position
    int head, tail, old_head, old_tail;
} q_t;


q_t* q_init() {
    q_t *q = (q_t *)malloc(sizeof(q_t));
    bzero(q->queue, sizeof(int*)*LEN);
    q->full = 0;
    q->a = 0;
    q->z = LEN-1;

    q->head = 0;
    q->old_head = 0;
    q->tail = 0;
    q->old_tail = 0;

    return q;
}

void* push (q_t *q, void *val) {

    // if queue is full
    if (q->full) {
        printf("full\n");
        return NULL;
    }
   
    q->queue[q->tail] = val;


    // move index before check if over bound
    if ((q->tail)+1 == LEN )
        q->tail = 0;
    else
        (q->tail)++;

    if (q->tail == q->head)
        q->full = true;

    return q->queue[q->tail];
}


void* pop (q_t *q) {

    if (q->head == q->tail && !q->full ) {
        printf("empty\n");
        return NULL;
    }

    




    void* ret = q->queue[q->head];

    // move index before check if over bound
    if ((q->head)+1 == LEN )
        q->head = 0;
    else
        (q->head)++;

    if (q->full)
        q->full = false;

    return ret;
}

void show(q_t *q) {

    printf("------------\n");
    
    n_t *tmp;
    
    for (int i=0; i<LEN; i++) {
        tmp = (n_t*)q->queue[i];

        if (tmp) {

            // if there is n_t at this position, print its value
            printf("q %d is %d at %p  ", i, ((n_t*)q->queue[i])->val, &(q->queue[i]));
        
        } else {
            
            // if no object at this position, simply print NUL 
            printf("q %d is NULL at %p  ", i, &(q->queue[i]));
        }

        if (i == q->head) {
            printf("h");
        } 
        if (i == q->tail) {
            printf("t");
        }
        printf("\n");
    }
}


int main () {

    int op;
    int input;

    q_t *q;
    q = q_init();

    show(q);

    while(1) {
        printf("op: ");
        scanf("%d", &op);
        if (op == 1) {
            printf("give val: ");
            scanf("%d", &input);
            n_t *n = (n_t*) malloc(sizeof(n_t));
            n->val = input;
            push(q, (void *) n);
        } else {
            pop(q);
        }

        printf("show: ---\n");
        show(q);
        
    }
}

#endif  /* ring_queue_h */
