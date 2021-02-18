

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
    
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE(arr) (int)sizeof(arr)/sizeof(arr[0])

#define SWAP(a, b) do {     \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while (0)

int len;
void show(int arr[])
{
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

/** Partition the input array in to 2 parts and sort. */
int quick_sort_partition (int arr[], int left, int right)
{
    printf("in this partition, left = %d, right = %d\n", left, right);

    int mid_idx = right;
    right--;
    int swap_with_mid_before_return = -1;

    for (;left < right; left++) {
        if (arr[left] > arr[mid_idx]) {     // if this one is larger then mid

            swap_with_mid_before_return = left;

            // find a small one from right
            for (; right > left ; right--) {
                if (arr[right] < arr[mid_idx]) {

                    // if find, then swap them
                    SWAP(arr[left], arr[right]);
                    show(arr);
                    swap_with_mid_before_return = right;
                    break;
                }
            }
        } 
    }

    if (swap_with_mid_before_return != -1) {
        SWAP(arr[swap_with_mid_before_return], arr[mid_idx]);
        printf("swap before return\n");
        show(arr);
        return swap_with_mid_before_return;
    } else {
        return right;
    }
}

void quick_sort(int arr[], int left, int right)
{
    if (right == left+1) {
        if (arr[left] > arr[right]) {
            SWAP(arr[left], arr[right]);
        }
        return;
    }

    int q;

    q = quick_sort_partition(arr, left, right);
    printf("partition return %d\n", q);
    

    if (q != left)
        quick_sort(arr, left, q);
    if (q != right)
        quick_sort(arr, q, right);
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){

#ifdef SORT
    // debug print
    printf("nums = [");
    for (int i=0; i<numsSize; i++) {
        printf("%d, ", nums[i]);
    }
    printf("]\n");

    printf("target = %d\n", target);


    // sort
    quick_sort(nums, 0, numsSize-1);
    show(nums);
#endif

    for (int i=0; i<numsSize-3; i++) {
        for (int j=i+1; j<numsSize-2; j++) {
            for (int k=j+1; k<numsSize-1; k++) {
                for (int m=k+1; m<numsSize; m++) {
                    if (nums[i]+nums[j]+nums[k]+nums[m] == target) {
                        printf("%d + %d + %d + %d = %d\n", nums[i], nums[j], nums[k], nums[m], target);
                    }
                }
            }
        }
    }
    return NULL;
}


int main () {

    int nums[] = {1, 0, -1, 0, -2, 2, 0, 0};
    int target = 0;
    len = ARR_SIZE(nums);

    int **ret;
    int returnSize;
    int *returnColumnSizes;
    ret = fourSum(nums, ARR_SIZE(nums), target, &returnSize, &returnColumnSizes);
    
}
