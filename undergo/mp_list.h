#ifndef MP_LIST_H
#define MP_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

struct mp_list_t {
    void *head;
    void *tail;
    void **next;
    int flag;
};


int mp_list_push(void *node, void **next, struct mp_list_t* mp_list) {

    do {
        //tmp_tail = mp_list->tail;
    } while( !__sync_bool_compare_and_swap(&(mp_list->flag), 0, 1));

    if (mp_list->head == NULL) {
        mp_list->head = node;
        mp_list->next = next;
        mp_list->tail = node;
    } else {
        *(mp_list->next) = node;
        mp_list->tail = node;
        mp_list->next = next;
    }
    mp_list->flag = 0;

    return 0;
}


struct mp_list_t* init_mp_list() {
    void* ret;
    ret = malloc(sizeof(struct mp_list_t));
    if (NULL != ret) {
        bzero(ret, sizeof(struct mp_list_t));
    }
    return (struct mp_list_t*) ret;
}


#endif 
