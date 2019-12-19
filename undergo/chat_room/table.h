#ifndef TABLE_H
#define TABLE_H

#define TABLE_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __table {
    void *arr[TABLE_SIZE];
    
} table_t;

table_t* init_table() {
    void* ret = malloc(sizeof(table_t));
    if (!ret) {
        return NULL;
    }
    bzero(ret, sizeof(table_t));
    return (table_t*) ret;
}

int table_add(int idx, table_t* table, void *node, void **next) {
    idx = idx % TABLE_SIZE;
    if (table->arr[idx]) {
        *next = table->arr[idx];
    }
    table->arr[idx] = node;
    return 0;
}

int table_remove(int idx, table_t* table, void* (iter_func)(void*), void* (match_func)(void*, int), int (link_func)(void*, void*)) {
    void* prev = NULL;
    void* curr = table->arr[idx % TABLE_SIZE];
    void* next;

    while (curr) {
        if (match_func(curr, idx)) {
            next = iter_func(curr);
            if (prev) {
                link_func(prev, next);
            } else {
                table->arr[idx % TABLE_SIZE] = next;
            }
            return 0;
        } else {
            prev = curr;
            curr = iter_func(prev);
        }
    }
    return -1;
}


void table_show(table_t* table, void* (iter_func)(void*), int (get_key)(void*)) {
    printf("------ table ------\n");
    void* curr;
    for (int i=0; i<TABLE_SIZE; i++) {
        printf("[ %d ] ", i);
        curr = table->arr[i];
        while (curr) {
            printf("%d ->", get_key(curr));
            curr = iter_func(curr);
        }
        printf("\n");
    }
    printf("-------------------\n");
}

#endif
