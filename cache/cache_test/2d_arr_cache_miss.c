/***
 File Name: 2d_arr.c
 Author: alen6516
 Created Time: 2019-07-16
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline long long rdtsc(void) {
    unsigned low, high;
    asm volatile ("rdtsc" :"=a"(low), "=d"(high));
    return ((low) | (uint64_t)(high) << 32);
}

int main() {

    int A = 5;
    int B = 100000;
    
    char arr[A][B];
    char tmp;

    arr[0][0] = 0;

    long long unsigned start, end;
   
    
    start = rdtsc();
    tmp = arr[0][0];
    end = rdtsc();
    printf("diff = %lld\n", end-start);

    start = rdtsc();
    tmp = arr[0][100];
    end = rdtsc();
    printf("diff = %lld\n", end-start);

    for (int j=0; j<1; j++) {
        for (int i=1; i<5; i++) {
            start = rdtsc();
            tmp = arr[i][j];
            end = rdtsc();
            printf("diff = %lld\n", end-start);
        }
    }
}
