#include <stdio.h>

#define SIZE 20

char* int_to_str(unsigned int num, int base) {
    static const char REP[] = "0123456789ABCDEF";
    static char buff[SIZE];
    char *p;
    p = &buff[SIZE-1];
    *p = '\0';

    do {
        *(--p) = REP[num % base];
        num /= base;
    } while (num != 0);

    return p;
}

int main () {

    printf("%s\n", int_to_str(4, 16));
}
