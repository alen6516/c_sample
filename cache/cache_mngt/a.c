/***
 File Name: a.c
 Author: alen6516
 Created Time: 2019-07-22
***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define chunk_size 32
#define thread_num 2 
#define chunk_num 5

#define MAX_pps 100000

// if chunk is occupied, change to true
bool ocupy[chunk_num] = { false };

// how many chunks have been occupied
int ocupy_num = 0;

// pool
int pool[chunk_num * chunk_size];

// counter for pkt per thread
unsigned long pkt_count[thread_num] = {0};
unsigned long pps = 100;
bool run = true;
unsigned long time_interval = 0;


void DEBUG(const char* func_name, const char *msg) {
    #ifdef DEBUG
        printf("In %10s, msg: %s\n", func_name, msg);
    #else
        (void)msg;
    #endif
}

void* umalloc() {

    int* ret = NULL;
    int index = -1;
    while (1) {
    
        index = (index==chunk_num-1) ? 0 : index+1;
        if ( ocupy[index] == true ) {

            printf("index %d has been occupied\n", index);

            if (ocupy_num == chunk_num) {
                printf("umalloc fail, no more chunks available\n");
                ret = NULL;
                break;
            }

            printf("but still available one, keep searching\n");

            continue;
        }
            
        if (  __sync_bool_compare_and_swap(&ocupy[index], false, true)   ) {

            printf("hit, occpupied index %d\n", index);


            __sync_fetch_and_add(&ocupy_num, 1);

            printf("occupy_num = %d\n", ocupy_num);
            
            ret = &pool[chunk_size * index];
            break;
        }
    }

    return (void*)ret;
}

void ufree(void *chunk_addr) {
    
    int index;
    int *addr = (int*) chunk_addr;

    index = (addr - pool) / chunk_size;
    __sync_fetch_and_sub(&ocupy_num, 1);

    ocupy[index] = false;
}


void* test(void* id_) {

    int *id = (int*) id_;

    int *addr;
    addr = (int*) umalloc();
    printf("index = %ld, addr = %p\n", (addr-pool)/chunk_size, addr);
    sleep(1);
    ufree((void*) addr);

    printf("%d exit\n", *id);
    return 0;
}

int main () {

    pthread_t t[5];


    for (int i=0; i<5; i++) {
        pthread_create(&t[i], NULL, test, (void*) &i);
    }

    pthread_join(t[4], NULL);

}
