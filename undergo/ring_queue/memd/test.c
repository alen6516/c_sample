#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "memd_queue.h"
#include "../getRandNum.h"

struct node_t {
    int val;
};

__thread int id;
int e_id = 1;
int d_id = 11;
int val = 0;

struct queue_t* queue;


void* en_work(void *arg) {

    id = e_id ++;

    struct node_t* node;

    while (1) {
        node = (struct node_t*) malloc(sizeof(struct node_t));
        while (1) {
            sleep(getRandNum() % 3);
            if ( en_queue((void*)node, queue) ) {
                printf("\ten_queue fail, thr %d\n", id);
                continue;
            } else {
                __sync_fetch_and_add( &val, 1);
                node->val = val;
                printf("en_queue val %d, thr %d\n", node->val, id);
                break;
            }
        }
    }

    return NULL;
}

void* de_work(void *arg) {
    id = d_id ++;

    struct node_t* node;
    while (1) {
        sleep(getRandNum() % 3);
        node = (struct node_t*) de_queue(queue);
        if (NULL == node) {
            //printf("\tde_queue fail, thr %d\n", id);
        } else {
            //printf("de_queue val %d, thr %d\n", node->val, id);
            printf("%d, thr %d\n", node->val, id);
            free(node);
        }
    }

    return NULL;
}

int main (int argc, char *argv[]) {
    
    int en_thr_num = 3;
    int de_thr_num = 3;

    if (argc == 3) {
        en_thr_num = strtol(argv[1], NULL, 10);
        de_thr_num = strtol(argv[2], NULL, 10);
    }

    printf("%d writer\n", en_thr_num);
    printf("%d reader\n", de_thr_num);

    if ( !(queue = init_queue()) ) {
        printf("malloc fail\n");
    }

    pthread_t en_t[en_thr_num];
    pthread_t de_t[de_thr_num];

    for (int i=0; i<en_thr_num; i++) {
        pthread_create(&en_t[i], NULL, en_work, NULL);
    }
    for (int i=0; i<de_thr_num; i++) {
        pthread_create(&de_t[i], NULL, de_work, NULL);
    }
   
    sleep(100);
}
