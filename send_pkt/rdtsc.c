/***
 File Name: rd.c
 Author: alen6516
 Created Time: 2019-07-16
***/

#include <stdint.h>

inline long long rdtsc(void) {
    unsigned low, high;
    asm volatile ("rdtsc" :"=a"(low), "=d"(high));
    return ((low) | (uint64_t)(high) << 32);
}
