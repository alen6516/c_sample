#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "sesd_queue.h"
#include "../getRandNum.h"

struct node_t {
    int val;
};

__thread int id;

struct queue_t* queue;


void* en_work(void *arg) {
    id = 1; 
    struct node_t* node;

    int val=0;
    while (1) {
        sleep(getRandNum() % 3);
        node = (struct node_t*) malloc(sizeof(struct node_t));
        node->val = val;
        if ( en_queue((void*)node, queue) ) {
            printf("\ten_queue fail, thr %d\n", id);
        } else {
            printf("en_queue val %d, thr %d\n", node->val, id);
            val++;
        }

    }

    return NULL;
}

void* de_work(void *arg) {
    id = 2;
    struct node_t* node;
    while (1) {
        sleep(getRandNum() % 3);
        node = (struct node_t*) de_queue(queue);
        if (NULL == node) {
            printf("\tde_queue fail, thr %d\n", id);
        } else {
            printf("%d, thr %d\n", node->val, id);
            free(node);
        }
    }

    return NULL;
}

int main (int argc, char *argv[]) {
    

    if ( !(queue = init_queue()) ) {
        printf("malloc fail\n");
    }

    pthread_t en_t;
    pthread_t de_t;

    pthread_create(&en_t, NULL, en_work, NULL);
    pthread_create(&de_t, NULL, de_work, NULL);
   

    sleep(100);
}
