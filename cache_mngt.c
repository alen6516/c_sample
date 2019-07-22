/***
 File Name: main.c
 Author: alen6516
 Created Time: 2019-07-19
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#define chunk_size (2*1024)
#define thread_num 1
#define chunk_num 5

#define MAX_pps 100000

// if chunk is occupied, change to true
bool ocupy[chunk_num] = { false };

// how many chunks have been occupied
int ocupy_num = 0;

// pool
char pool[chunk_num * chunk_size];

// counter for pkt per thread
unsigned long pkt_count[thread_num] = {0};
unsigned long pps = 1000;
bool run = true;
unsigned long time_interval = 0;
unsigned long clock_interval = 0;


void* umalloc();
void ufree(void*);
void* send_pkt(int);

void DEBUG(const char* func_name, const char *msg) {
    #ifdef DEBUG
        printf("In %10s, msg: %s\n", func_name, msg);
    #else
        (void)msg;
    #endif
}

void* send_pkt(int id) {
    
    char *my_chunk = (char*)umalloc();

    //int index = (my_chunk-pool)/chunk_size;

    //printf("thread id %d get index %d chunk\n", id, index);
    pkt_count[id]++;

    ufree((void*) my_chunk);
    //printf("thread id %d return index %d\n", id, index);
    return 0;
}



void* umalloc() {

    char* ret = NULL;
    int index = -1;
    while (1) {
    
        index = (index==chunk_num-1) ? 0 : index+1;
        if ( ocupy[index] == true ) {
    
            //printf("index %d has been occupied\n", index);
            if (ocupy_num == chunk_num) {
                //printf("umalloc fail, no more chunks available\n");
                ret = NULL;
                break;
            }
            //printf("but still chunk available, keep searching\n");
            continue;
        }
            
        if (  __sync_bool_compare_and_swap(&ocupy[index], false, true)   ) {
            __sync_fetch_and_add(&ocupy_num, 1);
            //printf("now occupy_num = %d\n", ocupy_num);
            ret = &pool[chunk_size * index];
            break;
        }
    
    }

    return (void*)ret;
}

void ufree(void *chunk_addr) {
    
    int index;
    char *addr = (char*) chunk_addr;

    index = (addr - pool) / chunk_size;
    __sync_fetch_and_sub(&ocupy_num, 1);
    ocupy[index] = false;
}


void* work_fun_time(void* id_) {


    int *id = (int*) id_;
    printf("thread id %d start\n", *id);

    struct timeval time_start;
    struct timeval time_end;
    unsigned long tmp_time_interval;


    gettimeofday(&time_start, NULL);

    while (run) {
        gettimeofday(&time_end, NULL);


        tmp_time_interval = 1000000*(time_end.tv_sec - time_start.tv_sec) + time_end.tv_usec - time_start.tv_usec;    


        if (tmp_time_interval < clock_interval) {

            if (thread_num > 1) {
                usleep(10);
            }

            continue;
        } else {
            send_pkt(*id);
            gettimeofday(&time_start, NULL);
        }
    
    }
    return 0;
}

void* work_fun_clock(void* id_) {


    int *id = (int*) id_;
    printf("thread id %d start\n", *id);


    clock_t clock_start;
    clock_t clock_end;
    clock_t tmp_clock_interval = 0;


    clock_start = clock();

    while (run) {

        if (tmp_clock_interval < clock_interval) {
            clock_end = clock();
            tmp_clock_interval = clock_end - clock_start;

            
            if (thread_num > 1) {
                usleep(10);
            }

            continue;
        } else {
            send_pkt(*id);
            tmp_clock_interval = 0;
            clock_start = clock();
        }
    
    }
    return 0;
}


void* report_fun() {

    unsigned long old_counter = 0;
    unsigned long new_counter = 0;
    while (run) {
        usleep(1000000);

        for(int i=0; i<thread_num; i++) {
            new_counter += pkt_count[i];
        }


        printf("pps = %ld, packet count in past 1 sec = %lu\n", pps, (new_counter - old_counter));
        old_counter = new_counter;
        new_counter = 0;
    }
    return 0;
    
}


void int_handler() {
    run = false;
    /**int _counter = counter;*/
    /***/
    /**gettimeofday(&end, NULL);*/
    /***/
    /**double diff = (double) (1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec)/1000000;*/
    /***/
    /**printf("totally send %d packets in %f secs\n", _counter, diff);*/

    printf("exit\n");
    
}


void tstp_handler() { 

    pps = (pps == MAX_pps) ? MAX_pps : pps+1000;
    printf("add pps, now pps is %ld\n", pps);
    time_interval = thread_num * 1000000/pps;
    clock_interval = thread_num * CLOCKS_PER_SEC/pps;
}

int main() {

    signal(SIGINT, int_handler);
    signal(SIGTSTP, tstp_handler);


    time_interval = thread_num * 1000000/pps;
    clock_interval = thread_num * CLOCKS_PER_SEC/pps;

    int id[thread_num];
    pthread_t work_thread[thread_num];
    pthread_t report_thread;


    pthread_create(&report_thread, NULL, report_fun, NULL);
    

    for (int i = 0; i < thread_num; i++) {

        id[i] = i;

        //printf("in main id = %d\n", id[i]);
        pthread_create(&work_thread[i], NULL, work_fun_time, (void*) &id[i]);
        
    }


    pthread_join(report_thread, NULL);

}

