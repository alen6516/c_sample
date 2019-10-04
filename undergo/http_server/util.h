#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdarg.h>

#define DEBUG ( (DEBUG_MODE==1) ? printf: do_nothing )
#define INFO  ( (INFO_MODE==1) ? printf: do_nothing )
#define ERROR ( (ERROR_MODE==1) ? printf: do_nothing )

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


#define SIZE_OF_ARR(arr) ((int)(sizeof(arr)/sizeof(arr[0])))


char const *weekday[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };


char const *month[] = { NULL, "Jan", "Feb", "Mar", "Apr", "May", "Jun" };



#endif



