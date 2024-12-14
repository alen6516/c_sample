#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

static int
partition (int arr[], int left, int right)
{

    //printf("in this partition, left = %d, right = %d\n", left, right);

    int mid_idx = right;
    right--;
    int swap_with_mid_before_return = -1;


    for (;left <= right; left++) {
        if (arr[left] > arr[mid_idx]) {     // if this one is larger then mid

            swap_with_mid_before_return = left;

            // find a small one from right
            for (; right > left ; right--) {
                if (arr[right] < arr[mid_idx]) {

                    // if find, then swap them
                    SWAP(arr[left], arr[right]);
                    //show();
                    swap_with_mid_before_return = right;
                    break;
                }
            }
        } 
    }

    if (swap_with_mid_before_return != -1) {
        SWAP(arr[swap_with_mid_before_return], arr[mid_idx]);
        //printf("swap before return\n");
        //show();
        return swap_with_mid_before_return;
    } else {
        return right;
    }
}

static void
quick_sort(int arr[], int left, int right)
{

    if (right == left+1) {
        if (arr[left] > arr[right]) {
            SWAP(arr[left], arr[right]);
        }
        return;
    }

    int q;

    q = partition(arr, left, right);
    
    if (q != left)
        quick_sort(arr, left, q);
    if (q != right)
        quick_sort(arr, q, right);
}

void
show_my_quick_sort(int *_arr, int len)
{
    int *arr = (int*) malloc(sizeof(int)*len);
    memcpy(arr, _arr, sizeof(int)*len);

    clock_t start_t, end_t;
    double total_t;
    printf("my_quick_sort: ============================\n");

    start_t = clock();
    quick_sort(arr, 0, len-1);
    end_t = clock();

    show_arr(arr, len);
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    printf("total: %f sec\n", total_t);
}
