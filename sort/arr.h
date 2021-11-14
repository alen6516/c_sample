#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SWAP(a, b) ({   \
    if ((a) != (b)) {   \
        a = a^b;        \
        b = a^b;        \
        a = a^b;        \
    }                   \
})

//int arr[] = {3, 4, 1, 5, 3, 2, 9, 0, 20,19,18,17,16,15, 14, 13, 12, 11};
//int len = sizeof(arr)/sizeof(int);

#define MAX_LEN 20
#define MAX_NUM 50

static inline void
init_arr(int **arr, int *len)
{
    srand(time(NULL));
    int _len = (rand() % MAX_LEN) +1;
    int *_arr = (int*) malloc(sizeof(int)*_len);
    for (int i=0; i<_len; i++) {
        _arr[i] = (rand() % MAX_NUM) + 1;
    }
    *arr = _arr;
    *len = _len;
}

static inline void
show_arr(int *arr, int len)
{
    printf("len = %d\n", len);
    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}

#endif
