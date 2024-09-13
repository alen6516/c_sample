#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

void selection_sort(int *arr, int len)
{
    int min;
    int idx;
    for (int i=0; i<len; i++) {
        min = arr[i];
        for (int j=i+1; j<len; j++) {
            if (arr[j] < min) {
                idx = j;
                min = arr[j];
            }
        }
        SWAP(arr[i], arr[idx]);
    }
}

void
show_selection_sort(int *_arr, int len)
{
    int *arr = (int*) malloc(sizeof(int)*len);
    memcpy(arr, _arr, sizeof(int)*len);

    clock_t start_t, end_t;
    double total_t;
    printf("selection_sort: =============================\n");

    start_t = clock();
    selection_sort(arr, len);
    end_t = clock();

    show_arr(arr, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
