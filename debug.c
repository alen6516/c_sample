#include <stdio.h>
#include <stdlib.h>

#define DEBUG

void _debug (const char *msg, const char* __file, const char* __func, const unsigned  __line) {

    #ifdef DEBUG
    printf("in file %s, func %s, line %d\n", __file, __func, __line);
    #endif

}

void foo() {
    _debug("this is foo", __FILE__, __func__, __LINE__);
}

int main() {
    foo();
}
