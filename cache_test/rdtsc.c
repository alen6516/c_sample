/***
 File Name: rdtsc.c
 Author: alen6516
 Created Time: 2019-07-15
***/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

static inline long long rdtsc(void) {
    unsigned low, high;
    asm volatile ("rdtsc" :"=a"(low), "=d"(high));
    return ((low) | ((uint64_t)(high) << 32));
}

double value;

int main () {

    long long unsigned int s,e;

    //printf("%llu\n", rdtsc());
    s = rdtsc();

	// perform 100 million integer divisions
    /*
	for (double count = 0; count < 100000000; count++)
		value = count / 10;
    */
    sleep((unsigned)1);
    e = rdtsc();
    //printf("%llu\n", rdtsc());
    
    printf("%lld\n", e-s);
}
