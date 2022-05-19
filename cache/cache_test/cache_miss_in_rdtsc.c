/***
 File Name: cache_miss_in_rdtsc.c
 Author: alen6516
 Created Time: 2019-07-15
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

    char arr[64*1024];
    
    char tmp;
    long long unsigned int start, end;

    tmp = arr[0];

    start = rdtsc();
    for (int i=0; i<10; i++) {
        tmp = arr[i];
    }
    end = rdtsc();
    printf("diff1 in rdtsc = %lld\n", end-start);

    for (int i=30000; i<30010; i++) {
        start = rdtsc();
        tmp = arr[i];
        end = rdtsc();
        printf("diff2 in rdtsc = %lld\n", end-start);
    }
    return 0;
}
