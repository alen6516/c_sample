#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../utils/arr.h"

void insert_sort(int *arr, int len) {

    int tmp;

    for (int i=1; i<len; i++) {
        for (int j=0; j<i; j++) {
            if (arr[i]>arr[j]) {
                // insert i in front of j
                if (i-1 == j) {
                    SWAP(arr[i], arr[j]);
                } else {
                    tmp = arr[i];
                    memmove(&arr[j+1], &arr[j], sizeof(int)*(i-j));
                    arr[j] = tmp;
                }
            }
        }
    }
}

void
show_insert_sort(int *_arr, int len)
{
    int *arr = (int*) malloc(sizeof(int)*len);
    memcpy(arr, _arr, sizeof(int)*len);

    clock_t start_t, end_t;
    double total_t;
    printf("insert_sort: ============================\n");

    start_t = clock();
    insert_sort(arr, len);
    end_t = clock();

    arr_show(arr, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
