/***
 File Name: gettime.c
 Author: alen6516
 Created Time: 2019-07-15
***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   /* timeval, gettimeofday() */
#include <unistd.h>     /* sleep() */

int main() {

    struct timeval start, end;
    gettimeofday(&start, NULL);
    sleep(1);
    gettimeofday(&end, NULL);

    unsigned long diff;
    diff = 1000000 * (end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec;
    printf("%ld\n", diff);
    return 0;
}   
