#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

extern char DEBUG;

void _debug(const char* func, const char* msg) {

    if (DEBUG)
        printf("in func %s: %s\n", func, msg);
}

#endif
