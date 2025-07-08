#include <stdio.h>
#include <string.h>
#include "../utils/arr.h"

/**
 * pick a pivot
 * find val larger and smaller than pivot
 * swap the larger and smaller one to put them the same side
 * go to right and left half, do the same process
 */

// sort into increasing order
void my_quick_sort(int *arr, int start, int end)
{
    if (start >= end || start < 0 || end < 0)
        return;

    int left, right;    // moving idx
    left = start;
    right = end;

    int p_idx = start;

    while (left != right) {
        // find smaller in right
        while (arr[p_idx] <= arr[right] && left < right) {
            right--;
            DEBUG("right is %d now\n", arr[right]);
        }

        // find larger in left
        while (arr[left] <= arr[p_idx] && left < right) {
            left++;
            DEBUG("left is %d now\n", arr[left]);
        }

        if (left < right) {
            SWAP(arr[left], arr[right]);
        }
    }

    if (arr[p_idx] != arr[left])
        SWAP(arr[p_idx], arr[left]);

    quick_sort(arr, start, right-1);
    quick_sort(arr, left+1, end);
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
    my_quick_sort(arr_out, 0, len-1);
    end_t = clock();

    arr_show(arr_out, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
