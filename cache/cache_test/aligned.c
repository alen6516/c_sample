/***
 File Name: a.c
 Author: alen6516
 Created Time: 2019-07-15
***/

#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

#include <sys/time.h>

int main () {

    int a __attribute__ ((aligned (16))) = 0;
    printf("%d\n", a);
}
