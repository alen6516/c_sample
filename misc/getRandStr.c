/***
 File Name: getRandStr.c
 Author: alen6516
 Created Time: 2019-06-28
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

extern int getRandNum();

char *getRandString(size_t len) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890,./<>?`~!@#$%^&*()-=_+[]{}|\\'\"";

    if (len < 2) {
        fprintf(stderr, "The given length must larger than 1.\n");
        return NULL;
    }

    char *result = (char *)malloc(sizeof(char)*(len+1));
    int key;
    for (int i=0; i<len; i++) {
        if ((key = getRandNum()) == -1) {
            fprintf(stderr, "Could not get random number.\n");
            return NULL;
        }
        key = key % ((int)sizeof(charset)-1);
        //printf("%d\n", key);
        result[i] = charset[key];
    }
    result[len] = '\0';
    return result;
}

static void test_getRandStr() {
    int len = 10;
    char *str = (char *)malloc(sizeof(char)*(len+1));
    str = getRandString(len);
    printf("%s\n", str);
}
