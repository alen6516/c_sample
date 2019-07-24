/***
 File Name: test.c
 Author: alen6516
 Created Time: 2019-07-15
***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

clock_t start, end;

int main () {
    long arr[64000];
    for (long i=0; i<32000; i++)
        arr[(int)i] = i;
    
    
    long tmp;

    start = clock();
    for(int j=0; j<32000; j++) 
        tmp = arr[j];
    end = clock();

    printf("diff1 in clock = %ld\n", end-start);


    start = clock();
    for(int j=32000; j<64000; j++) 
        tmp = arr[j];
    end = clock();
    

    printf("diff2 in clock = %ld\n", end-start);
   
}
