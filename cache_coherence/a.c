/***
 File Name: a.c
 Author: alen6516
 Created Time: 2019-07-29
***/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "rdtsc.h"

#define COUNT 1000000000


typedef struct {

    long count;

} Counter;


Counter arr[2];


void *thread(void *index_) {

    int *index = (int*) index_;

    int i;
    for (i=0; i<COUNT; i++) {
        arr[*index].count ++;
    }

    return 0;

}


int main () {

    arr[0].count = 0;
    arr[1].count = 0;

    unsigned long long start, end;

    pthread_t t1, t2;

    int id1 = 0, id2 = 1;

    start = rdtsc();

    pthread_create(&t1, NULL, thread, &id1);
    pthread_create(&t2, NULL, thread, &id2);

   
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    end = rdtsc();

    printf("%lld\n", end-start);
}
