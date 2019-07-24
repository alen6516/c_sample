/***
 File Name: main.c
 Author: alen6516
 Created Time: 2019-07-18
***/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "ring_queue.h"

#define TEST_LEN 100

q_t *q;

int arr[TEST_LEN];

/*
void test () {

    int op;
    int input;

    q_t * qq = q_init();

    show(qq);

    while(1) {
        printf("op: ");
        scanf("%d", &op);
        if (op == 1) {
            printf("give val: ");
            scanf("%d", &input);
            n_t *n = (n_t*) malloc(sizeof(n_t));
            n->val = input;
            push(qq, (void *) n);
        } else {
            pop(qq);
        }

        printf("show: ---\n");
        show(qq);
        
    }

}
*/
int getRandNum() {
    FILE *fp;
    if ((fp = fopen("/dev/urandom", "r")) == NULL) {
        fprintf(stderr, "Error!, Could not open /dev/urandom to read.\n");
        return -1;
    }

    int result = fgetc(fp);
    return result;
}


void* p_th() {
    
    void *r;
    
    for (int i=0; i < TEST_LEN; i++) {
        /**sleep(getRandNum() % 5);*/
        r = push(q, (void*) &arr[i]);
        if (r) {
            printf("producer push %d\n", arr[i]);
        } else {
            printf("producer can not push\n");
        }
        usleep(10);
    }
    
    printf("producer finished\n");
    pthread_exit(0);
}

void* c_th() {

    void *r;
    int _len = 0;
    while (_len < TEST_LEN) {
    
        /**sleep(getRandNum() % 5);*/
        r = pop(q);
        if (r) {
            printf("consumer pop %d\n", *(int*)r);
            _len++;
        } else {
            printf("consumer can not pop\n");
        }
        usleep(10);
    }
    pthread_exit(0);
}

int main () {

    q = q_init();

    for (int i=0; i<TEST_LEN; i++) {
        arr[i] = i;
    }

    pthread_t pt, ct;
    pthread_create(&pt, NULL, p_th, NULL);
    pthread_create(&ct, NULL, c_th, NULL);

    pthread_join(pt, NULL);
    pthread_join(ct, NULL);

    /**test();*/
}
