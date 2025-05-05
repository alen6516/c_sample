#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// maintain an array to track the first-k largerst element
// len: current array len
// size: array size
void insert_to_arr(int *arr, int *len, int size, int val)
{
    int i=0;
    for (; i < (*len); i++) {
        if (val >= arr[i]) {
            if (i < size-1)     // if not the last one, we need to memmove
                memmove(&arr[i], &arr[i+1], sizeof(int)*(size-i-1));
            arr[i] = val;
            goto out;
        }
    }
    if (i < size)   // if array not full, need to append
        arr[i] = val;

out:
    if (*len < size) (*len)++;
}

int findKthLargest(int* nums, int numsSize, int k) {

    int *arr = (int*) malloc(sizeof(int)*k);
    int len = 0;
    //memset(arr, 0, sizeof(int)*k);

    for (int i=0; i<k; i++) {
        insert_to_arr(arr, &len, k, nums[i]);
    }

    return arr[k-1];
}
