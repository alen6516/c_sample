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

int LEN = 5;

typedef struct node {
    int val;
} n_t;


typedef struct queue {
    void* queue[5];
    int real_len;
   
    // current index position
    int pro_head, pro_tail, con_head, con_tail;
} q_t;


q_t* q_init() {
    q_t *q = (q_t *)malloc(sizeof(q_t));
    /**q->queue = malloc(sizeof(void*)*LEN);*/
    /**bzero(q->queue, sizeof(int*)*LEN);*/
    q->real_len = 0;

    return q;
}

void* push (q_t *q, void *val) {

    // if queue is full
    if ( __sync_bool_compare_and_swap(&LEN, q->real_len, LEN )){
        return NULL;
        
    }
   
    int tmp_pro_head;
    int new_pro_head;


    // check if I can reserve 

    while (1) {
    
        tmp_pro_head = q->pro_head % LEN;
        new_pro_head = (tmp_pro_head+1) % LEN;
       
        if ( __sync_bool_compare_and_swap( &(q->pro_head), tmp_pro_head, new_pro_head) ) {
            break;
        } else {
            continue;
        }
    }


    // do push
    q->queue[tmp_pro_head] = val;


    // check if I can release
    
    int tmp_pro_tail;
    int new_pro_tail;

    while (1) {
        
        tmp_pro_tail = q->pro_tail;
        new_pro_tail = tmp_pro_tail+1;
       
        if ( __sync_bool_compare_and_swap( &(q->pro_tail), tmp_pro_tail, new_pro_tail) ) {
            break;
        } else {
            continue;
        }
    
    }

    return q->queue[tmp_pro_head];
}


void* pop (q_t *q) {

    // if queue is full
    if ( __sync_bool_compare_and_swap(&LEN, q->real_len, LEN )){
        return NULL;
        
    }


    int tmp_con_head;
    int new_con_head;


    // check if I can reserve 

    while (1) {
    
        tmp_con_head = q->con_head % LEN;
        new_con_head = (tmp_con_head+1) % LEN;
       
        if ( __sync_bool_compare_and_swap( &(q->con_head), tmp_con_head, new_con_head) ) {
            break;
        } else {
            continue;
        }
    }


    // check if I can release
    
    int tmp_con_tail;
    int new_con_tail;

    while (1) {
        
        tmp_con_tail = q->con_tail;
        new_con_tail = tmp_con_tail+1;
       
        if ( __sync_bool_compare_and_swap( &(q->con_tail), tmp_con_tail, new_con_tail) ) {
            break;
        } else {
            continue;
        }
    
    }


    return q->queue[tmp_con_head];
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
            printf("q %d is NULL at %p  ", i, (q->queue[i]));
        }

        if (i == q->pro_head) {
            printf("ph ");
        } 
        if (i == q->pro_tail) {
            printf("pt ");
        }
        if (i == q->con_head) {
            printf("ch ");
        } 
        if (i == q->con_tail) {
            printf("ct ");
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
