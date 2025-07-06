#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../utils/arr.h"


// sort into increasing order
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
        while(key < arr[right] && left < right) {
            right --;
        }

        while(arr[left] <= key && left < right) {
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

// sort into decreasing order
static void
quick_sort_reverse(int *arr, int start, int end)
{
    if (start >= end || start < 0 || end < 0) {
        return;
    }

    int left, right;
    left = start;
    right = end;
    int key = arr[start];

    // [ 1 3 1 0 4]
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

    quick_sort_reverse(arr, left+1, end);
    quick_sort_reverse(arr, start, left-1);
}

void
show_quick_sort(int *arr_in, int len)
{
    int *arr_out = (int*) malloc(sizeof(int)*len);
    memcpy(arr_out, arr_in, sizeof(int)*len);

    clock_t start_t, end_t;
    double total_t;
    printf("quick_sort: =============================\n");

    start_t = clock();
    quick_sort(arr_out, 0, len-1);
    end_t = clock();

    arr_show(arr_out, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);


    // test reverse
    memcpy(arr_out, arr_in, sizeof(int)*len);
    printf("quick_sort_reverse: =====================\n");

    start_t = clock();
    quick_sort_reverse(arr_out, 0, len-1);
    end_t = clock();

    arr_show(arr_out, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
