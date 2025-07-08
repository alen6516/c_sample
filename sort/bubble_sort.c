#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/arr.h"

void bubble_sort(int *arr, int len)
{
    for (int i=0; i<len; i++) {
        for (int j=i; j<len; j++) {
            if (arr[i] < arr[j]) {
                SWAP(arr[i], arr[j]);
            }
        }
    }
}

void
show_bubble_sort(int *_arr, int len)
{
    int *arr = (int*) malloc(sizeof(int)*len);
    memcpy(arr, _arr, sizeof(int)*len);

    clock_t start_t, end_t;
    double total_t;
    printf("bubble_sort: =============================\n");

    start_t = clock();
    bubble_sort(arr, len);
    end_t = clock();

    arr_show(arr, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
