#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

void quick_sort(int[], int, int);

int main ()
{    
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    quick_sort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    end_t = clock();
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    show();
    printf("total: %f sec\n", total_t);
}


// still not correct
void quick_sort(int arr[], int start, int end)
{
    if (start >= end || start < 0 || end < 0) {
        return;
    }

    int left, right;
    left = start;
    right = end;
    int key = arr[start];

    while(left != right) {
        while(arr[right] < key && left < right) {
            right --;
        }

        while(arr[left] >= key && left < right) {
            left ++;
        }

        if (right > left) {
            SWAP(arr[left], arr[right]);
        }
    }
    SWAP(arr[start], arr[left]);

    quick_sort(arr, start, left-1);
    quick_sort(arr, left+1, end);
}
