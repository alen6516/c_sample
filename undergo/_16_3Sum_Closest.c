/*
 * Runtime: 28 ms, faster than 34.72% of C online submissions for 3Sum Closest.
 * Memory Usage: 6.9 MB, less than 100.00% of C online submissions for 3Sum Closest.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 3

#define ARR_LEN(arr) ((int)(sizeof(arr)/sizeof(arr[0])))

#define abs(a) ((a)>0 ? (a) : (0-(a)))

#define SWAP(a, b) do {     \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while (0);

int partition (int arr[], int left, int right) {

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

int threeSumClosest(int* nums, int numsSize, int target) {

    if(numsSize == 3) {
        return nums[0]+nums[1]+nums[2];
    }

    quick_sort(nums, 0, numsSize-1);
    
    int left=0, mid = 1, right = numsSize-1;
    int curr_sum;

    int cont = 1;
    int check_if_too_large = 1;

    while(cont && right>mid && mid>left) {
        curr_sum = nums[left]+nums[mid]+nums[right];
        if (curr_sum-target > 0) {
            if (check_if_too_large) {
                right--;
                mid = left+1;
                continue;
            } else {
                break;
            }
        } else if (curr_sum-target < 0) {
            if (!check_if_too_large) {
                left++;
                mid = right-1;
                continue;
            } else {
                check_if_too_large = 0;
                mid = right-1;
                continue;
            }
        }
    }

    for (int i=left; i<=right; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    return 0;
}


int main () {
    int nums[] = {-50, -40, -39, -20, -15, -14, 0, 10, 20, 100, 200};
    int len = ARR_LEN(nums);
    for (int i=0; i<len; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    quick_sort(nums, 0, len-1);

    int target = 1;
    threeSumClosest(nums, len, target);
}
