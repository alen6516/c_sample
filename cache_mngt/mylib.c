/***
 File Name: main.c
 Author: alen6516
 Created Time: 2019-07-19
***/

#ifndef _FUNC_H
#define _FUNC_H


#include <stdbool.h>
#include <stdlib.h>


/* function gloabl */
#define chunk_size (2*1024)
#define chunk_num 5
bool ocupy[chunk_num] = { false };  // if chunk is occupied, change to true
int ocupy_num = 0;                  // how many chunks have been occupied
char pool[chunk_num * chunk_size];  // pool


void* umalloc();
void ufree(void*);


/* lib func */
void* umalloc() {

    char* ret = NULL;
    int index = -1;
    while (1) {
        index = (index==chunk_num-1) ? 0 : index+1;
        if ( ocupy[index] == true ) {
            if (ocupy_num == chunk_num) {
                ret = NULL;
                break;
            }
            continue;
        }
        if (  __sync_bool_compare_and_swap(&ocupy[index], false, true)   ) {
            __sync_fetch_and_add(&ocupy_num, 1);
            ret = &pool[chunk_size * index];
            break;
        }
    }
    return (void*)ret;
}


/* lib func */
void ufree(void *chunk_addr) {
    int index;
    char *addr = (char*) chunk_addr;
    index = (addr - pool) / chunk_size;
    __sync_fetch_and_sub(&ocupy_num, 1);
    ocupy[index] = false;
}


#endif  /* _FUNC_H */
