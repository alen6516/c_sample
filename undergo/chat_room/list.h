#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __list {
    void *head;
    void **next;
    __sig_atomic_t len;
} list_t;


list_t* init_list() {
    void* ret = malloc(sizeof(list_t));
    if (!ret) {
        return NULL;
    }
    bzero(ret, sizeof(list_t));
    return (list_t*) ret;
}


int list_put(list_t* list, void* node, void** next) {
    if (!list || !node || !next) {
        return -1;
    }

    void** tmp_next;
    do {
        tmp_next = list->next;
    } while (!__sync_bool_compare_and_swap(&list->next, tmp_next, next));

    if (tmp_next == NULL) {
        // list is empty
        list->head = node;
    } else {
        *tmp_next = node;
    }

    return 0;
}


void* list_take(list_t* list, void* (get_next)(void*)) {
    if (!list) {
        return NULL;
    }

    void *ret = NULL;
    ret = list->head;
    list->head = get_next(ret);
    return ret;
}

#endif
