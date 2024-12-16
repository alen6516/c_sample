/***
 File Name: main.c
 Author: alen6516
 Created Time: 2019-07-19
***/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include "mylib.c"


/* test global */
#define thread_num 1
#define MAX_pps 100000
unsigned long pps = 1000;
bool run = true;
unsigned long time_interval = 0;
unsigned long clock_interval = 0;

typedef struct {
    unsigned long count;
    char padding[56];
} count_t;                          
count_t pkt_count[thread_num];      // counter of pkt for each thread


/* tool func */
void debug_(const char* func_name, const char *msg) {
    #ifdef DEBUG
        printf("In %10s, msg: %s\n", func_name, msg);
    #else
        (void)msg;
    #endif
}



/* test func */
void* send_pkt(int id) {
    char *my_chunk = (char*)umalloc();
    pkt_count[id].count++;
    ufree((void*) my_chunk);
    return 0;
}



/* test func */
void* work_fun_time(void* id_) {
    
    int *id = (int*) id_;
    

    char s[20];
    sprintf(s, "thread id %d start\n", *id);
    debug_(__func__, s);


    pkt_count[*id].count = 0;


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


/* test func */
void* work_fun_clock(void* id_) {

    int *id = (int*) id_;
    char s[20];
    sprintf(s, "thread id %d start\n", *id);
    debug_(__func__, s);


    //init pkt_count
    pkt_count[*id].count = 0;


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


/* test func */
void* report_fun() {

    unsigned long old_counter = 0;
    unsigned long new_counter = 0;
    while (run) {
        usleep(1000000);

        for(int i=0; i<thread_num; i++) {
            new_counter += pkt_count[i].count;
        }


        printf("pps = %ld, packet count in past 1 sec = %lu\n", pps, (new_counter - old_counter));
        old_counter = new_counter;
        new_counter = 0;
    }
    return 0;
    
}


/* test func */
void int_handler() {
    run = false;
    printf("exit\n");
}


/* test func */
void tstp_handler() { 

    pps = (pps == MAX_pps) ? MAX_pps : pps+1000;
    printf("add pps, now pps is %ld\n", pps);
    time_interval = thread_num * 1000000/pps;
    clock_interval = thread_num * CLOCKS_PER_SEC/pps;
}

int main(int argc, char *argv[]) {

    if (argc > 1) {
        pps = atoi(argv[1]);
    }

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
        pthread_create(&work_thread[i], NULL, work_fun_clock, (void*) &id[i]);
    }


    pthread_join(report_thread, NULL);

}
