#ifndef WORK_LIST_H
#define WORK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * producer just append task to the tail of the list,
 * once comsumer work, he will take tasks from head until all tasks are taken.
 *
 * 1. no length limit, need to count to know the len
 * 2. 1 reader 1 writer can be no contention
 * 3. no pop api, the reader need to iterate by itself
 */

struct list_t {
    void *head;
    void **curr_next;   // *(list->curr_next) is the next node's addr
};

void* list_init() {
    
    void* ret;
    ret = malloc(sizeof(struct list_t));
    if (ret) {
        bzero(ret, sizeof(struct list_t));
        return ret;
    } else {
        return NULL;
    }
}

int list_push(void* node, void** next, struct list_t* list) {

    if (list->head == NULL) {
        // list is empty
        //printf("header is NULL, push node\n");
        list->head = node;
        list->curr_next = next;

    } else {
        *(list->curr_next) = node;
        list->curr_next = next;
    }

    return 0;
}

#endif
