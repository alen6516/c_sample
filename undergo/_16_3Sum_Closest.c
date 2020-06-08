/*
 * Runtime: 28 ms, faster than 34.72% of C online submissions for 3Sum Closest.
 * Memory Usage: 6.9 MB, less than 100.00% of C online submissions for 3Sum Closest.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


// compare if it is a smaller diff
void check_and_replace(int target, int left, int mid, int right, int nums[], int *diff) {

    int is_change = 0;
    int sum;
    sum = nums[left] + nums[mid] + nums[right];

    if (abs(*diff) > abs(target-sum)) {
        *diff = sum-target;
        is_change = 1;
    }

    /*
    if (target == 0) {
        if (abs(*diff) > abs(sum)) {
            *diff = sum;
            is_change = 1;
        }
    } else if (target > 0) {
        if (sum >= 0) {
            if (abs(*diff) > abs(target-sum)) {
                *diff = sum-target;
                is_change = 1;
            }
        } else {
            if (*diff > target-sum) {
                *diff = target-sum;
                is_change = 1;
            }
        }
    } else {
        if (sum >= 0) {
            if (*diff > sum-target) {
                *diff = sum-target;
                is_change = 1;
            }
        } else {
            if (*diff > abs(sum-target)) {
                *diff = abs(sum-target);
                is_change = 1;
            }
        }
    }
    */
    // debug print
    if (is_change) {
        printf("idx %d %d %d make new closest sum %d, the new diff is %d\n", left, mid, right, sum, *diff);
    }
}

void walk_through(int nums[], int left, int right, int target, int *diff) {
    if (right - left < 2) {
        return ;
    }


    for (int mid = left +1; mid<right; mid++) {
        check_and_replace(target, left, mid, right, nums, diff);
        if (*diff == 0) {
            return;
        }
    }
}


void cut(int nums[], int left, int right, int target, int *diff) {

    if (right-left < 2) return;
    else if (right-left == 2) {
        check_and_replace(target, left, left+1, right, nums, diff);
        if (*diff == 0) {
            return ;
        }
    }

    int mid=left+1;
    int check_if_too_large =1;
    int curr_sum;

    while(right>mid && mid>left) {
        curr_sum = nums[left]+nums[mid]+nums[right];

        check_and_replace(target, left, mid, right, nums, diff);
        if (*diff == 0) {
            return;
        }

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

    walk_through(nums, left, right, target, diff);
    if (*diff == 0) {
        return ;
    }

    cut(nums, left+1, right, target, diff);
    if (*diff == 0) {
        return ;
    }
    cut(nums, left, right-1, target, diff);
    if (*diff == 0) {
        return ;
    }

}


int threeSumClosest(int* nums, int numsSize, int target) {

    if(numsSize == 3) {
        return nums[0]+nums[1]+nums[2];
    }

    // do a quick sort
    quick_sort(nums, 0, numsSize-1);

    // debug print for quick sort
    for (int i=0; i<numsSize; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    

    // the algurithm
    int left=0, right = numsSize-1;
    int diff = 100;
    cut(nums, left, right, target, &diff);
    
    printf("sum = %d\n", target+diff);
    return target + diff;
}


int main () {
    int nums[] = {1, 1, 1, 2};
    int len = ARR_LEN(nums);
    int target = 0;
    printf("target = %d\n", target);
    for (int i=0; i<len; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    /*
    quick_sort(nums, 0, len-1);
    for (int i=0; i<len; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    */
    threeSumClosest(nums, len, target);
}
