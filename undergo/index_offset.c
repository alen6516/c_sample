/***
 File Name: index_offset.c
 Author: alen6516
 Created Time: 2019-08-05
***/

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    void *pointer;
} fp;


typedef struct {
    short index;
} fi;


typedef struct {
    int counter;
} data_t;

data_t arr[5];

int main () {

    
    // pointer
    fp p1, p2, p3, p4, p5;
    p1.pointer = (void*) &arr[0];
    p2.pointer = (void*) &arr[1];
    p3.pointer = (void*) &arr[2];
    p4.pointer = (void*) &arr[3];
    p5.pointer = (void*) &arr[4];


    // base + index * offset
    char *base = (char*) &arr[0];
    unsigned int offset = sizeof(data_t);
    fi i1, i2, i3, i4, i5;
    i1.index = 0;
    i2.index = 1;
    i3.index = 2;
    i4.index = 3;
    i5.index = 4;

    
    // test
    printf("%p\n", p1.pointer);
    printf("%p\n", base + i1.index*offset);

    printf("%p\n", p2.pointer);
    printf("%p\n", base + i2.index*offset);


    printf("sizeof fp = %d\n", (int)sizeof(fp));
    printf("sizeof fi = %d\n", (int)sizeof(fi));
}
