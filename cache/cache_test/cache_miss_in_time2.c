/***
 File Name: cache_miss_in_rdtsc.c
 Author: alen6516
 Created Time: 2019-07-15
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

int main() {

    long arr[512000];
    for (long i=0; i<256000; i++)
        arr[(int)i] = i;
    
    long tmp, diff1, diff2;
    struct timeval start1, end1;
    struct timeval start2, end2;

    gettimeofday(&start1, NULL);
    tmp = arr[0];
    gettimeofday(&end1, NULL);
    diff1 = 1000000 * (end1.tv_sec - start1.tv_sec) + end1.tv_usec - start1.tv_usec;
    printf("diff1 in time2 = %ld\n", diff1);



    gettimeofday(&start2, NULL);
    tmp = arr[512000-1];
    gettimeofday(&end2, NULL);
    diff2 = 1000000 * (end2.tv_sec - start2.tv_sec) + end2.tv_usec - start2.tv_usec;
    printf("diff2 in time2 = %ld\n", diff2);

}
