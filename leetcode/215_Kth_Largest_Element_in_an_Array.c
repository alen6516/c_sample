#include <stdio.h>
#include <stdlib.h>



// maintain an array to track the first-k largerst element
void insert_to_arr(int *arr, int len, int val)
{
    if (len == 0) {
        arr[0] = val;
        return;
    }

}

int findKthLargest(int* nums, int numsSize, int k) {

    int *arr = (int*) malloc(sizeof(int)*k);
    memset(arr, 0, sizeof(int)*k);

    for (int i=0; i<k; i++) {
        insert_to_arr(arr, i, nums[i]);
    }
}
