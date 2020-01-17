#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "node.h"

#define P_NUM 2
#define N_NUM 4

list_t* list;

_Atomic int g_val = 0;

_Atomic int _id = 0;
__thread int my_id;

void* putter(void* arg) {
    my_id = ++_id;
    node_t* node;
    for (int i=0; i<N_NUM; i++) {
        node = node_init();
        node->val = rand() % 10;
        g_val += node->val;
        sleep(rand() % 3);
        list_put(list, (void*)node, (void**)&node->next);
        printf("putter %d put val %d to list\n", my_id, node->val);
    }
    return NULL;
}

void* taker(void* arg) {
    int i=0;
    void* out;
    int sum = 0;
    while (i< P_NUM*N_NUM) {
        sleep(rand() % 3);
        out = list_take(list, node_get_next, node_link, node_get_ref_of_next);
        if (!out) {
            printf("take fail\n");
            continue;
        }
        printf("take val = %d\n", ((node_t*)out)->val);
        sum += ((node_t*)out)->val;
        i++;
    }
    printf("sum = %d\n", sum);

    return NULL;
}

int main () {

    srand(time(NULL));

    node_t* root = node_init();

    list = list_init((void*)root, node_get_ref_of_next);
    
    pthread_t parr[P_NUM];
    for (int i=0; i<P_NUM; i++) {
        pthread_create(&parr[i], NULL, putter, NULL);
    }

    pthread_t ta;
    pthread_create(&ta, NULL, taker, NULL);

    pthread_join(ta, NULL);
}

