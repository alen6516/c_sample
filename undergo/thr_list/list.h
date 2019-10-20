#include <stdio.h>
#include <stdlib.h>

#define MAX_THREAD_NUM 100

struct thr_node_t {
    // use array to store

    unsigned int my_id;
    unsigned int next_ava_id;    // MAX_NUM if no avaliable node

};

struct thr_node_t thr_arr[MAX_THREAD_NUM] = {{0}};

struct thr_list_t {
    unsigned int head_id;
    unsigned int tail_id;
};


int thr_list_pop(struct thr_list_t* thr_list) {
    int ret_id = thr_list->head_id;
    thr_list->head_id = thr_arr[ret_id].next_ava_id;
    return ret_id;
    // receiver need to check if it is MAX_NUM
}

int thr_list_push(unsigned int id, struct thr_list_t* thr_list) {
    unsigned int tail_id;
    
    thr_arr[id].next_ava_id = MAX_THREAD_NUM;

    do {
        tail_id = thr_list->tail_id;
    } while( !__sync_bool_compare_and_swap(&(thr_list->tail_id), tail_id, id));

    return 0;
}

