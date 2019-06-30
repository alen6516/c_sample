/***
 File Name: ring_queue.c
 Author: alen6516
 Created Time: 2019-07-01
***/

#include <stdio.h>
#include <stdlib.h>
//gcc 5.4.0

#define LEN 50


typedef struct queue {
    int queue[LEN];
    int len = 0;
    
    int *a, *z;
    a = &queue[0];
    z = &queue[Len-1];

    int *head, *tail;
    head = &queue[0];
    tail = &queue[0];
} q_t;


int push(q_t);
int pop(q_t);

int push (q_t *q, int val) {
    if (q->len == LEN-1)
        return 1;
    
    q->len++;
    *(q->tail) = val;
    (q->tail)++;


    // check if over bound
    if (q->tail > q->z)
        q->tail = q->a;
}


int pop (q_t *q) {

    if (q->len == 0 )
        return -1;
    
    
    q->len--;
    int ret = *(q->head);
    (q->head)++;


    // check if over bound
    if (q->head > q->z)
        q->head = q->a;

    return ret;
}

int main () {


}
