#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/arr.h"

// find the min after i, and swap with i
void selection_sort(int *arr, int len)
{
    int min;
    for (int i=0; i<len-1; i++) {
        min = i;
        for (int j=i+1; j<len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        SWAP(arr[i], arr[min]);
    }
}

void
show_selection_sort(int *arr_in, int len)
{
    int *arr_out = (int*) malloc(sizeof(int)*len);
    memcpy(arr_out, arr_in, sizeof(int)*len);

    printf("selection_sort: =============================\n");

    CLOCK_START();
    selection_sort(arr_out, len);
    CLOCK_END();

    arr_show(arr_out, len);
    printf("total: %f sec\n", CLOCK_DIFF_SEC());

    free(arr_out);
}
