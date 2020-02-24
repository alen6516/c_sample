#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "node.h"

#define P_NUM 3
#define T_NUM 2
#define N_NUM 4

list_t* list;

_Atomic int g_sum = 0;
_Atomic int taken = 0;

_Atomic int _id = 0;
__thread int my_id;

void* putter(void* arg) {
    my_id = ++_id;
    node_t* node;
    for (int i=0; i<N_NUM; i++) {
        node = node_init();
        node->val = rand() % 10;
        sleep(rand() % 3);
        list_put(list, (void*)node, (void**)&node->next);
        printf("putter %d put val %d to list\n", my_id, node->val);
    }
    return NULL;
}

void* taker(void* arg) {
    void* out;
    while (taken< P_NUM*N_NUM) {
        sleep(rand() % 3);
        out = list_take(list, node_get_next, node_link, node_get_ref_of_next);
        if (!out) {
            printf("take fail\n");
            continue;
        }
        printf("take val = %d\n", ((node_t*)out)->val);
        g_sum += ((node_t*)out)->val;
        taken++;
    }
    printf("sum = %d\n", g_sum);

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

    pthread_t tarr[T_NUM];
    for (int i=0; i<N_NUM; i++) {
        pthread_create(&tarr[i], NULL, taker, NULL);
    }

    for (int i=0; i<T_NUM; i++) {
        pthread_join(tarr[i], NULL);
    }
}

