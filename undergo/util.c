#include <stdio.h>

int do_nothing(const char *format, ...) {
    //printf("in test\n");
    return 0;
}
#define ASSERT(con, msg) ( ((con)==0) ? printf("[ASSERT FAIL] %s", (msg)): do_nothing((msg)) )

#define SIZE_OF_ARR(arr) ((int)(sizeof(arr)/sizeof(arr[0])))


