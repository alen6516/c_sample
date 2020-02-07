#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

int partition(int[], int, int);
void quick_sort(int[], int, int);


int main () {
    
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    quick_sort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    end_t = clock();
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    print_arr();
    printf("total: %f sec\n", total_t);
}

int partition (int arr[], int left, int right) {

    /*
    if (left == right-1) {
        if (arr[left] > arr[right])
            SWAP(arr[left], arr[right]);
        return 0;
    }
    */

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
                    swap_with_mid_before_return = right;
                    break;
                }
            }
        } 
    }

    if (swap_with_mid_before_return != -1) {
        SWAP(arr[swap_with_mid_before_return], arr[mid_idx]);
        return swap_with_mid_before_return;
    } else {
        return right;
    }
}

void quick_sort(int arr[], int left, int right) {

    int q;

    q = partition(arr, left, right);
    
    if (q != left && q != left+1)
        quick_sort(arr, left, q);
    if (q != right && q != right-1)
        quick_sort(arr, q, right);
}
