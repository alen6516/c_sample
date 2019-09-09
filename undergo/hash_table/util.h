#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

void _debug(const char* func, const char* msg) {

    #ifdef DEBUG
    printf("in func %s: %s\n", func, msg);
    #endif
}

#endif
