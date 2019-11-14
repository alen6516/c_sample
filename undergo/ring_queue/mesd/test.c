#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "mesd_queue.h"
#include "../getRandNum.h"

struct node_t {
    int val;
};

__thread int id;

struct queue_t* queue;


void* en_work(void *arg) {
    static int _id = 1;
    id = _id++;
    struct node_t* node;

    static int val=0;
    while (1) {
        sleep(getRandNum() % 4);
        node = (struct node_t*) malloc(sizeof(struct node_t));
        node->val = val;
        if ( en_queue((void*)node, queue) ) {
            printf("\ten_queue fail, thr %d\n", id);
        } else {
            printf("en_queue val %d, thr %d\n", node->val, id);
            __sync_fetch_and_add( &val, 1);
        }
    }
    return NULL;
}

void* de_work(void *arg) {
    id = 0; 
    struct node_t* node;
    while (1) {
        sleep(getRandNum() % 2);
        node = (struct node_t*) de_queue(queue);
        if (NULL == node) {
            printf("\tde_queue fail, thr %d\n", id);
        } else {
            //printf("de_queue val %d, thr %d\n", node->val, id);
            printf("%d, thr %d\n", node->val, id);
            free(node);
        }
    }

    return NULL;
}

int main (int argc, char *argv[]) {
    
    int thr_num = 3;

    if (argc == 2) {
        thr_num = strtol(argv[1], NULL, 10);
    }

    printf("%d writer\n", thr_num);

    if ( !(queue = init_queue()) ) {
        printf("malloc fail\n");
    }

    pthread_t en_t[thr_num];
    pthread_t de_t;

    for (int i=0; i<thr_num; i++) {
        pthread_create(&en_t[i], NULL, en_work, NULL);
    }
    pthread_create(&de_t, NULL, de_work, NULL);
   

    sleep(100);
}
