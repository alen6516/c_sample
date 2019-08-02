/***
 File Name: vector.c
 Author: alen6516
 Created Time: 2019-08-01
***/

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void vector_init(vector *v) {
    
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = (void **)malloc(sizeof(void *) * v->capacity);

}

int vector_total(vector *v) {
    return v->total;
}

static void vector_resize(vector *v, int capacity) {

    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", v->capacity, capacity);
    #endif

    void **items = (void **)realloc (v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_add(vector *v, void *item) {

    if (v->capacity == v->total)
        vector_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

