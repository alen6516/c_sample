#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/arr.h"

static void heapify(int *arr, int len, int i)
{
    if (len == 1) return;

    // compare i with its left & right child and swap
    int right = (i+1)*2;
    int left = (i+1)*2-1;
    int largest = i;

    if (right < len && arr[largest] < arr[right])
        largest = right;

    if (left < len && arr[largest] < arr[left])
        largest = left;

    if (largest != i) {
        SWAP(arr[largest], arr[i]);

        heapify(arr, len, largest); // heapify the affected subtree
    }
}

static void bheap_sort(int *arr, int len)
{
    if (len == 1) return;

    // i is the last idx having left or right child
    for (int i=len/2-1; i>=0; i--) {    // heapify from i to 0
        heapify(arr, len, i);         // so we will have largest at root
    }

    // i means how many elements sorted
    for (int i=1; i<len; i++) {
        // swap root with current last idx, so the largest goes end
        SWAP(arr[0], arr[len-i]);

        heapify(arr, len-i, 0);
    }
}

void show_my_bheap_sort(int *arr_in, int len)
{
    int *arr_out = (int *)malloc(sizeof(int)*len);
    memcpy(arr_out, arr_in, sizeof(int)*len);
    printf("my_bheap_sort: =============================\n");

    CLOCK_START();
    bheap_sort(arr_out, len);
    CLOCK_END();

    arr_show(arr_out, len);
    printf("total: %f sec\n", CLOCK_DIFF_SEC());

    free(arr_out);
}
