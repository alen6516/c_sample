#include <stdio.h>
#include "arr.h"
#include "utils.h"


// sort into increasing order
void quick_sort(int *arr, int start, int end)
{
    if (start >= end || start < 0 || end < 0)
        return;


    int left, right;
    left = start;
    right = end;

    int p_idx; p_val;
    p_idx = start;
    p_val = arr[p_idx];

    // [ 5, 3, 2, 6, 8, 1]


    while (left != right) {
        // find smaller in right
        while (p_val <= arr[right] && left < right) {
            right--;
            DEBUG("right is %d now\n", arr[right]);
        }

        // find larger in left
        while (arr[left] <= p_val && left < right) {
            left++;
            DEBUG("left is %d now\n", arr[left]);
        }

        if (left < right) {
            SWAP(arr[left], arr[right]);
        }
    }

    if (arr[p_idx] != arr[left])    // left may equal to p_idx
        SWAP(arr[p_idx], arr[left]);

    quick_sort(arr, start, right-1);
    quick_sort(arr, left+1, end);
}
