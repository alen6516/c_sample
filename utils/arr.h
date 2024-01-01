#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_MAX_SIZE    20
#define MAX_RAND_NUM    50

#define SIZE_OF_ARR(arr) ((int)(sizeof(arr)/sizeof(arr[0])))

/**
 * Create and return an array with random content.
 *
 * @[in] size: size of the array, 0 means use random size
 * @return: pointer to the array
 */
static inline int*
arr_create(int *size)
{
    if (!size) return NULL;

    srand(time(NULL));
    int *arr = NULL;

    if (*size == 0) {
        // use a random size for the array
        *size = (rand() % ARR_MAX_SIZE) +1;
    }

    arr = (int*) malloc(sizeof(int) * (*size));
    if (!arr) return NULL;

    for (int i=0; i<(*size); i++) {
        arr[i] = (rand() % MAX_RAND_NUM) + 1;
    }

    return arr;
}

static inline void
arr_show(int *arr, int size)
{
    for (int i=0; i<size; i++) {
        if (i == 0)
            printf("[%d", arr[i]);
        else
            printf(", %d", arr[i]);
    }
    printf("]\n");
    printf("array size = %d\n", size);
}

#endif
