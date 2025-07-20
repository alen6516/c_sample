#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
show_insert_sort(int *arr_in, int len)
{
    int *arr_out = (int*) malloc(sizeof(int)*len);
    memcpy(arr_out, arr_in, sizeof(int)*len);

    printf("insert_sort: ============================\n");

    CLOCK_START();
    insert_sort(arr_out, len);
    CLOCK_END();

    arr_show(arr_out, len);
    printf("total: %f sec\n", CLOCK_DIFF_SEC());

    free(arr_out);
}
