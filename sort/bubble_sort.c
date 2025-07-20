#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
show_bubble_sort(int *arr_in, int len)
{
    int *arr_out = (int*) malloc(sizeof(int)*len);
    memcpy(arr_out, arr_in, sizeof(int)*len);

    printf("bubble_sort: =============================\n");

    CLOCK_START();
    bubble_sort(arr_out, len);
    CLOCK_END();

    arr_show(arr_out, len);
    printf("total: %f sec\n", CLOCK_DIFF_SEC());

    free(arr_out);
}
