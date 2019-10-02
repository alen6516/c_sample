#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdarg.h>


#define DEBUG ( (DEBUG_MODE==1) ? printf: do_nothing )

int do_nothing(const char *msg,...) {
    //printf("in test\n");
    return 0;
}



/*
void _debug(const char* func, const char* msg) {

    #ifdef DENUG
        printf("in func %s: %s\n", func, msg);
    #endif
}
*/




#endif



