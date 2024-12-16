/***
 File Name: test.c
 Author: alen6516
 Created Time: 2019-07-19
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int member;
} item;

int main() {

    char s[10];
   
    strcpy(s, "123");

    printf("%s\n", s);


    item *t;
    t->member;
}


