/***
 File Name: ring_queue.c
 Author: alen6516
 Created Time: 2019-07-01
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//gcc 5.4.0

#define LEN 5

typedef struct queue {
    int queue[LEN];
    bool full;
    
    // boundary of the ring queue
    int *a;
    int *z;

    // current index position
    int *head, *tail;
} q_t;


q_t* init() {
    q_t *q = (q_t *)malloc(sizeof(q_t));
    q->full = 0;
    q->a = &(q->queue[0]);
    q->z = &(q->queue[LEN-1]);

    q->head = &(q->queue[0]);
    q->tail = &(q->queue[0]);

    return q;
}

void* push (q_t *q, int val) {

    // if queue is full
    if (q->full) {
        printf("full\n");
        return NULL;
    }
    
    *(q->tail) = val;


    // move index before check if over bound
    if ((q->tail)+1 > (q->z) )
        q->tail = q->a;
    else
        (q->tail)++;

    if (q->tail == q->head)
        q->full = true;

    return (void*)q->tail;
}


int pop (q_t *q) {

    if (q->head == q->tail && !q->full ) {
        printf("empty\n");
        return -1;
    }
    
    int ret = *(q->head);


    // move index before check if over bound
    if ((q->head)+1 > (q->z) )
        q->head = q->a;
    else
        (q->head)++;

    if (q->full)
        q->full = false;

    return ret;
}

void show(q_t *q) {

    printf("------------\n");
    for (int i=0; i<LEN; i++) {
        printf("q %d is %d at %p  ", i, *((q->a)+i), (q->a)+i);

        if ((q->a)+i == q->head) {
            printf("h");
        } 
        if ((q->a)+i == q->tail) {
            printf("t");
        }
        printf("\n");
    }
}

int main () {

    int op;
    int input;

    q_t *q;
    q = init();

    show(q);

    while(1) {
        printf("op: ");
        scanf("%d", &op);
        if (op == 1) {
            printf("give val: ");
            scanf("%d", &input);
            push(q, input);
        } else {
            pop(q);
        }

        printf("show: ---\n");
        show(q);
        
    }


}
