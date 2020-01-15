#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct __list {
    void *root;
    void **next;
} list_t;

list_t* list_init(void* root, void** (node_get_ref_of_next)(void*)) {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    if (!list) {
        return NULL;
    }
    bzero(list, sizeof(list_t));

    list->root = root;
    list->next = node_get_ref_of_next(root);

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


void* list_take(list_t* list, void* (node_get_next)(void*), int (node_link)(void*, void*)) {

    if (!list) {
        return NULL;
    }

    void *ret = NULL;

    ret = node_get_next(list->root);
    if (ret) {
        node_link(list->root, node_get_next(ret));
    }

    return ret;
}

#endif
