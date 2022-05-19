/***
 File Name: test.c
 Author: alen6516
 Created Time: 2019-07-15
***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

clock_t start, end;

int main () {
    long arr[64000];
    for (long i=0; i<32000; i++)
        arr[(int)i] = i;
    
    
    long tmp, diff1, diff2;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    for(int j=0; j<32000; j++) 
        tmp = arr[j];
    gettimeofday(&end, NULL);
    diff1 = 1000000 * (end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec;

    printf("diff1 in ms = %ld\n", diff1);


    gettimeofday(&start, NULL);
    for(int j=32000; j<64000; j++) 
        tmp = arr[j];
    gettimeofday(&end, NULL);
    diff2 = (1000000 * end.tv_sec + end.tv_usec) - (1000000* start.tv_sec + start.tv_usec);

    printf("diff2 in ms = %ld\n", diff2);
}
