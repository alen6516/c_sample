#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

static void
quick_sort(int *arr, int start, int end)
{
    if (start >= end || start < 0 || end < 0) {
        return;
    }

    int left, right;
    left = start;
    right = end;
    int key = arr[start];

    while(left != right) {
        while(key > arr[right] && left < right) {
            right --;
        }

        while(arr[left] >= key && left < right) {
            left ++;
        }

        if (left < right) {
            SWAP(arr[left], arr[right]);
        }
    }
    SWAP(arr[start], arr[left]);

    quick_sort(arr, left+1, end);
    quick_sort(arr, start, left-1);
}

void
show_quick_sort(int *_arr, int len)
{
    int *arr = (int*) malloc(sizeof(int)*len);
    memcpy(arr, _arr, sizeof(int)*len);

    clock_t start_t, end_t;
    double total_t;
    printf("quick_sort: =============================\n");

    start_t = clock();
    quick_sort(arr, 0, len-1);
    end_t = clock();

    show_arr(arr, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
