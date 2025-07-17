#include <stdio.h>
#include <string.h>
#include "../utils/utils.h"

void heapify();
void bheap_sort(int *arr, int len);
void show_bheap_sort(int *_arr, int len);

void heapify(int *arr, int len, int i)
{
    // compare i with its left & right child and swap
    int right = (i+1)*2;
    int left = (i+1)*2-1;
    int largest = i;

    if (right < len && arr[largest] < arr[right])
        largest = right;

    if (left < len && arr[largest] < arr[left])
        largest = left;

    SWAP(arr[largest], arr[i]);
}

void bheap_sort(int *arr, int len)
{
    int i = 0, j;
    while (i<len-1) {
        // j is the last idx having left or right child
        for (j=(len-i)/2-1; j>=0; j--) {
            heapify(arr, len-i, j);
        }

        // swap root with current last idx, so the largest goes end
        SWAP(arr[0], arr[len-i-1]);
        i++;    // i means how many elements processed
    }
}

void show_bheap_sort(int *_arr, int len)
{
    int *arr = (int *)malloc(sizeof(int)*len);
    memcpy(arr, _arr, sizeof(int)*len);
    double total_t;
    printf("bheap_sort: =============================\n");

    start_t = clock();
    bheap_sort(arr, len);
    end_t = clock();

    arr_show(arr, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
