#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***** node *****/
typedef struct __node {
    int val;
    struct __node* next;
} node_t;

node_t* init_node() {
    void* node;
    node = (node_t*)malloc(sizeof(node_t));
    if (!node) {
        return NULL;
    }
    bzero(node, sizeof(node_t));
    return (node_t*)node;
}

void** get_ref_of_next(void* node) {
    return (void**)&((node_t*)node)->next;
}

void* get_next(void* node) {
    return ((node_t*)node)->next;
}


/***** list *****/
typedef struct __list {
    void *root;
    void **next;
} list_t;

list_t* init_list(void* root, void** (get_ref_of_next)(void*)) {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    if (!list) {
        return NULL;
    }
    bzero(list, sizeof(list_t));

    list->root = root;
    list->next = get_ref_of_next(root);

    return list;
}


int list_put(list_t* list, void* node, void** next) {
    if (!list || !node || !next) {
        return -1;
    }

    void** tmp_next;
    do {
        tmp_next = list->next;
    } while (!__sync_bool_compare_and_swap(&list->next, tmp_next, next));

    *tmp_next = node;

    return 0;
}


void* list_take(list_t* list, void* (get_next)(void*)) {

    if (!list) {
        return NULL;
    }

    void *ret = NULL;

    ret = get_next(list->root);
    if (ret) {
        ((node_t*)(list->root))->next = (node_t*)get_next(ret);
    }

    return ret;
}

#endif
