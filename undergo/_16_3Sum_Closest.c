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

void check_and_replace(int target, int left, int mid, int right, int nums[], int *record) {

    int diff, sum;
    sum = nums[left] + nums[mid] + nums[right];
    if (target * *(record) >= 0 ) {
        diff = abs(target - *(record));
    } else {
        if (target > *record) {
            diff = target - *(record);
        } else {
            diff = *(record) - target;
        }
    }

    if (target == 0) {
        if (diff > abs(sum)) {
            *record = abs(sum);
            printf("idx %d %d %d make new closest sum %d\n", left, mid, right, sum);
        }
    } else if (target > 0) {
        if (sum >= 0) {
            if (diff > abs(target-sum)) {
                *record = abs(target-sum);
                printf("idx %d %d %d make new closest sum %d\n", left, mid, right, sum);
            }
        } else {
            if (diff > target-sum) {
                *record = target-sum;
                printf("idx %d %d %d make new closest sum %d\n", left, mid, right, sum);
            }
        }
    } else {
        if (sum >= 0) {
            if (diff > sum-target) {
                *record = sum-target;
                printf("idx %d %d %d make new closest sum %d\n", left, mid, right, sum);
            }
        } else {
            if (diff > abs(sum-target)) {
                *record = abs(sum-target);
                printf("idx %d %d %d make new closest sum %d\n", left, mid, right, sum);
            }
        }
    }
}

void walk_through(int nums[], int left, int right, int target, int *closest_num) {
    if (right - left < 2) {
        return ;
    }

    for (int mid = left +1; mid<right; mid++) {
        check_and_replace(target, left, mid, right, nums, closest_num);
    }
}


void cut(int nums[], int left, int right, int target, int *closest_num) {


    if (right-left < 2) return;
    else if (right-left == 2) {
        check_and_replace(target, left, left, right, nums, closest_num);
        return;
    }

    int mid=left+1;
    int check_if_too_large =1;
    int curr_sum;

    while(right>mid && mid>left) {
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

    walk_through(nums, left, right, target, closest_num);


    cut(nums, left+1, right, target, closest_num);
    cut(nums, left, right-1, target, closest_num);

}


int threeSumClosest(int* nums, int numsSize, int target) {

    if(numsSize == 3) {
        return nums[0]+nums[1]+nums[2];
    }

    quick_sort(nums, 0, numsSize-1);
    
    int left=0, right = numsSize-1;

    /*
    for (int i=left; i<=right; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    */

    int closest_num = 100;
    cut(nums, left, right, target, &closest_num);



    return 0;
}


int main () {
    int nums[] = {-50, -40, -39, -20, -15, -14, 0, 10, 20, 100, 200};
    int len = ARR_LEN(nums);
    int target = 1;
    printf("target = %d\n", target);
    for (int i=0; i<len; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");

    quick_sort(nums, 0, len-1);

    threeSumClosest(nums, len, target);
}
