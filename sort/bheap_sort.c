#include <stdio.h>
#include <string.h>

void heapify();
void bheap_sort(int *arr, int len);
void show_bheap_sort(int *_arr, int len);

void bheap_sort(int *arr, int len)
{
    // 1. build max heap
    // 2. swap root with last idx, and heapify with len-1 again
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
