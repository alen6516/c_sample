/***
 File Name: test_endian.c
 Author: alen6516
 Created Time: 2019-06-19
***/

#include <stdio.h>
#include <stdlib.h>

int main () {
    char pb[10];
    pb[0] = 0x12;
    pb[1] = 0x34;
    pb[2] = 0x56;
    pb[3] = 0x78;

    unsigned int *p, val;
    p = (unsigned int *)pb;
    val = *p;

    if (val == 0x12345678)
        printf("big endian\n");
    else if (val == 0x78563412)
        printf("little endian\n");
}
