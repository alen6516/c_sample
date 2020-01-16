#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "node.h"

#define LEN 2

list_t* list;

_Atomic int g_val = 0;

_Atomic int _id = 0;
__thread int my_id;

void* putter(void* arg) {
    my_id = ++_id;
    node_t* node;
    for (int i=0; i<2; i++) {
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
    while (1) {
        sleep(rand() % 3);
        out = list_take(list, node_get_next, node_link);
        if (!out) {
            /*
            printf("take fail\n");
            continue;
            */
            break;
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
    
    pthread_t parr[LEN];
    for (int i=0; i<LEN; i++) {
        pthread_create(&parr[i], NULL, putter, NULL);
    }

    sleep(5);
    pthread_t ta;
    pthread_create(&ta, NULL, taker, NULL);

    pthread_join(ta, NULL);
}

