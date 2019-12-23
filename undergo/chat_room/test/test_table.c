#include <stdio.h>
#include "../table.h"


typedef struct __node {
    int key;
    struct __node* next;
} node_t;


void* iter_func(void* node) {
    if (node) {
        return ((node_t*) node)->next;
    }
    return NULL;
}

int match_func(void* a, int key) {
    return ((node_t*)a)->key == key;
}

int link_func(void* a, void* b) {
    int ret = 0;
    if (a) {
        ((node_t*)a)->next = (node_t*)b;
        ret = 1;
    }
    return ret;
}

int get_key(void *node) {
    if (node) {
        return ((node_t*)node)->key;
    }
    return -1;
}


node_t* init_node(int key) {
    node_t* ret = (node_t*) malloc(sizeof(node_t));
    if (ret) {
        ret->key = key;
        ret->next = NULL;
    }
    return ret;
}


int main() {

    table_t *table;
    table = init_table();


    int arr[] = {2, 8, 9, 17, 21, 4, 23, 3, 1, 45, 10, 324, 213, 13, 873, 46, 765, 762, 54, 27, 43, 88, 53, 76};
    int len = sizeof(arr)/sizeof(int);


    node_t* tmp;
    for(int i=0; i<len; i++) {
        tmp = init_node(arr[i]);
        if (tmp) {
            table_add(get_key, table, (void*)tmp, (void**)&(tmp->next));
        }
    }

    table_show(table, iter_func, get_key);
    table_remove(1, table, get_key, iter_func, match_func, link_func);
    table_show(table, iter_func, get_key);
} 
