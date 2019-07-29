#ifndef _RDTSC_H
#define _RDTSC_H

#include <stdint.h>

static inline long long rdtsc(void) {
    unsigned low, high;
    asm volatile ("rdtsc" :"=a"(low), "=d"(high));
    return ((low) | ((uint64_t)(high) << 32));
}

#endif
