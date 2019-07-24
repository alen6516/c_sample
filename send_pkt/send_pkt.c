/***
 File Name: a.c
 Author: alen6516
 Created Time: 2019-07-16
***/

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>   /* gettimeofday */
#include <time.h>       /* clock_t */
#include <unistd.h>     /* sleep() */
#include <stdint.h>

#include <signal.h>
#include <pthread.h>

#define MAX_rate 100000

volatile int run = 1;
unsigned int counter = 0;
unsigned long rate = 0;
unsigned long long clock_diff = 0;

struct timeval start, end;



void send_packet();
void int_handler();
void tstp_handler();
void* func1();
void my_sleep(int);

static inline long long rdtsc(void) {
    unsigned low, high;
    asm volatile ("rdtsc" :"=a"(low), "=d"(high));
    return ((low) | (uint64_t)(high) << 32);
}

void send_packet() {
    ;
}

void int_handler() {
    run = 0;
    int _counter = counter;
    
    gettimeofday(&end, NULL);

    double diff = (double) (1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec)/1000000;

    printf("totally send %d packets in %f secs\n", _counter, diff);
    
}

void tstp_handler() { 
    if (rate + 1000 > MAX_rate)
        rate = MAX_rate;
    else
        rate = rate + 1000;

    printf("add rate, now rate is %ld\n", rate);
    clock_diff = CLOCKS_PER_SEC/rate;
}


void* func1() {
    int old_counter = 0;
    int new_counter;
    while (run) {
        usleep(1000000);
        new_counter = counter;
        printf("rate = %ld, packet count in past 1 sec = %d\n", rate, (new_counter - old_counter));
        old_counter = new_counter;
        //clock_diff = CLOCKS_PER_SEC/rate;
    }
    return 0;
}


int main(int argc, char *argv[]) {

    pthread_t t;


    int wait_interval = 0;


    if (argc > 1) {
        rate = atoi(argv[1]);
    } else {
        rate = 1000;
    }

    /**clock_t clock_start, clock_end;*/
    unsigned long long clock_start, clock_end;
    clock_diff = CLOCKS_PER_SEC/rate;
    //printf("clock_per_sec = %llu\n", (unsigned long long)CLOCKS_PER_SEC);
    //printf("clock_diff = %lld\n", clock_diff);

    signal(SIGINT, int_handler);
    signal(SIGTSTP, tstp_handler);

    gettimeofday(&start, NULL);
    pthread_create(&t, NULL, func1, "func1");

    //gettimeofday(&poll_start, NULL);
    
    clock_start = clock(); 
    
    
    while (run) {

        if (wait_interval < clock_diff) {
            clock_end = clock();
            wait_interval = (int) clock_end - clock_start;
        } else {
            counter++;
            wait_interval = 0;
            
            clock_start = clock();
        }
    }


    return 0;
}
