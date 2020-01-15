#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "node.h"

#define LEN 5

list_t* list;

_Atomic int g_val = 0;

void* putter(void* arg) {

    node_t* node = node_init();
    node->val = rand() % 10;
    g_val += node->val;
    sleep(rand() % 3);
    list_put(list, (void*)node, (void**)&node->next);

    return NULL;
}

void* taker(void* arg) {
    int i=0;
    void* out;
    int sum = 0;
    while (i<LEN) {
        sleep(rand() % 3);
        out = list_take(list, node_get_next, node_link);
        if (!out) continue;
        printf("val = %d\n", ((node_t*)out)->val);
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
    
    pthread_t parr[10];
    for (int i=0; i<LEN; i++) {
        pthread_create(&parr[i], NULL, putter, NULL);
    }

    sleep(5);

    void *out;
    int sum = 0;
    
    while ((out = list_take(list, node_get_next, node_link))) {
        printf("val = %d\n", ((node_t*)out)->val);
        sum += ((node_t*)out)->val;
    }
    printf("g_val = %d, sum = %d\n", g_val, sum);
}

