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

    int tmp_index;
    int new_index;


    // check if I can reserve 

    while (1) {
    
        tmp_index = q->pro_head;
        new_index = (tmp_index+1) % LEN;


        // full
        if ( tmp_index == q->con_tail && q->real_len == LEN) {
            printf("full\n");
            return NULL;
        }

       
        if ( __sync_bool_compare_and_swap( &(q->pro_head), tmp_index, new_index) ) {
            break;
        } else {
            continue;
        }
    }


    // do push
    q->queue[tmp_index] = val;
    void* ret = q->queue[tmp_index];


    // check if I can release
    
    while (1) {
        
        tmp_index = q->pro_tail;
        new_index = (tmp_index+1) % LEN;
       
        if ( __sync_bool_compare_and_swap( &(q->pro_tail), tmp_index, new_index) ) {
            __sync_fetch_and_add(&q->real_len, 1);
            break;
        } else {
            continue;
        }
    
    }


    return ret;
}


void* pop (q_t *q) {


    int tmp_index;
    int new_index;


    // check if I can reserve 

    while (1) {
    
        tmp_index = q->con_head;
        new_index = (tmp_index+1) % LEN;
       
        
        // empty
        if ( tmp_index == q->pro_tail && q->real_len == 0) {
            printf("empty\n");
            return NULL;
        }


        if ( __sync_bool_compare_and_swap( &(q->con_head), tmp_index, new_index) ) {
            break;
        } else {
            continue;
        }
    }


    void* ret = q->queue[tmp_index];
    q->queue[tmp_index] = NULL;

    // check if I can release

    while (1) {
        
        tmp_index = q->con_tail;
        new_index = (tmp_index+1) % LEN;
       
        if ( __sync_bool_compare_and_swap( &(q->con_tail), tmp_index, new_index) ) {
            __sync_fetch_and_sub(&q->real_len, 1);
            break;
        } else {
            continue;
        }
    
    }


    return ret;
}

void show(q_t *q) {

    printf("------------\n");
    
    void *tmp;
    
    for (int i=0; i<LEN; i++) {
        tmp = q->queue[i];

        if (tmp) {

            // if there is n_t at this position, print its value
            printf("q %d is %8d at %8p  ", i, ((n_t*)tmp)->val, tmp);
        
        } else {
            
            // if no object at this position, simply print NUL 
            printf("q %d is %8s at %8p  ", i, "NULL", tmp);
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
