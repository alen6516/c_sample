/***
 File Name: getRandNum.c
 Author: alen6516
 Created Time: 2019-06-28
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

int getRandNum() {
    FILE *fp;
    if ((fp = fopen("/dev/urandom", "r")) == NULL) {
        fprintf(stderr, "Error!, Could not open /dev/urandom to read.\n");
        return -1;
    }

    int result = fgetc(fp);
    return result;
}

static void test_getRandNum() {
    int i = getRandNum();
    assert(i >= 0);
}
