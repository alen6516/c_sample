#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD_NUM 10


/*
 * intent to implement a lockless list
 */

struct thr_node_t {
    // use array to store
    pthread_t thr;
    unsigned int my_id;
    unsigned int next_id;    // MAX_NUM if no avaliable node

};

struct thr_node_t thr_arr[MAX_THREAD_NUM] = {{0}};

struct thr_list_t {
    unsigned int head_id;
    unsigned int tail_id;
};

struct thr_list_t* thr_list;

int thr_list_pop(struct thr_list_t* thr_list) {
    int ret_id = thr_list->head_id;
    thr_list->head_id = thr_arr[ret_id].next_id;
    return ret_id;
    // receiver need to check if it is -1
}

int thr_list_push(int id, struct thr_list_t* thr_list) {
    int tail_id;
    
    thr_arr[id].next_id = -1;

    do {
        tail_id = thr_list->tail_id;
    } while ( !__sync_bool_compare_and_swap(&(thr_arr[tail_id].next_id), -1, id));
    thr_list->tail_id = id;

    return 0;
}

void* init_thr_list() {
    for (int i=0; i<MAX_THREAD_NUM; i++) {
        thr_arr[i].my_id = i;
        thr_arr[i].next_id = i+1;
    }
    thr_arr[MAX_THREAD_NUM-1].next_id = -1;

    ret = malloc(sizeof(struct thr_list_t*));
    if (NULL != ret) {
        bzero(ret, sizeof(struct thr_list_t));
        ((struct thr_list_t*)ret)->head_id = 0;
        ((struct thr_list_t*)ret)->tail_id = MAX_THREAD_NUM-1;
    }
    return ret;

}
