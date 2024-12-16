/*
Runtime: 12 ms, faster than 43.62% of C online submissions for 3Sum Closest.
Memory Usage: 5.9 MB, less than 71.81% of C online submissions for 3Sum Closest.
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


// compare if it is a smaller diff
/*
void check_and_replace(int target, int left, int mid, int right, int nums[], int *diff) {

    int is_change = 0;
    int sum;
    sum = nums[left] + nums[mid] + nums[right];

    if (abs(*diff) > abs(target-sum)) {
        *diff = sum-target;
        is_change = 1;
    }

    // debug print
    if (is_change) {
        printf("idx %d %d %d make new closest sum %d, the new diff is %d\n", left, mid, right, sum, *diff);
    }
}
*/

/** Check if input tuple makes closer result, replace the result if so. */
#define check_and_replace(target, left, mid, right, nums, diff) ({  \
    int is_change = 0;                                              \
    int sum;                                                        \
    sum = nums[left] + nums[mid] + nums[right];                     \
    if (abs(*diff) > abs(sum-target)) {                             \
        *diff = sum-target;                                         \
        is_change = 1;                                              \
    }                                                               \
    if (is_change) {                                                \
        printf("idx %d %d %d make new closest sum %d, the new diff is %d\n", left, mid, right, sum, *diff); \
    }                                                               \
})

// walk through every element from left to right and check
void walk_through(int nums[], int left, int right, int target, int *diff) {
    printf("walk start, left %d, right %d\n", left, right);

    for (int mid = left +1; mid<right; mid++) {
        check_and_replace(target, left, mid, right, nums, diff);
        if (*diff == 0) {
            return;
        }
    }
    printf("walk ends\n");
}

/** The algorithm */
void cut(int nums[], int left, int right, int target, int *diff) {

    /*
    if (right-left < 2) return;
    else if (right-left == 2) {
        check_and_replace(target, left, left+1, right, nums, diff);
        if (*diff == 0) {
            return ;
        }
    }
    */

    int mid=left+1;

    // find the smallest right
    check_and_replace(target, left, mid, right, nums, diff);
    if (*diff == 0) {
        return;
    }
    while ((nums[left]+nums[mid]+nums[right]) - target > 0) {
        if (right - 1 == mid) {
            break;
        }
        right --;
        check_and_replace(target, left, mid, right, nums, diff);
        if (*diff == 0) {
            return;
        }
    }
    printf("find the smallest right: %d\n", right);

    mid = right - 1;

    // find the largest left
    check_and_replace(target, left, mid, right, nums, diff);
    if (*diff == 0) {
        return;
    }
    while ((nums[left]+nums[mid]+nums[right]) - target < 0) {
        if (left + 1 == mid) {
            break;
        }
        left ++;
        check_and_replace(target, left, mid, right, nums, diff);
        if (*diff == 0) {
            return;
        }
    }
    printf("find the largest left: %d\n", left);

    mid = left+1;
    while(right > mid && mid > left) {

        for (int i=0; right-i > mid; i++) {
            walk_through(nums, left, right-i, target, diff);
            if (*diff == 0) {
                return ;
            }
        }

        left ++;
        mid = left+1;
    }
    return;
}


int threeSumClosest(int* nums, int numsSize, int target) {

    if(numsSize == 3) {
        return nums[0]+nums[1]+nums[2];
    }

    // do a quick sort
    quick_sort(nums, 0, numsSize-1);

    // check quick sort result
    for (int i=0; i<numsSize; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    printf("====== sort ends =======\n\n");
    

    // do the algurithm
    int left=0, right = numsSize-1;
    int diff = (nums[0] + nums[1] + nums[numsSize-1]) - target;
    cut(nums, left, right, target, &diff);
    
    printf("sum = %d\n", target+diff);
    return target + diff;
}


int main () {
    // init
    //int nums[] = {-23, -13, -8, -3, 0, 1, 7, 11, 25, 30, 31};
    //int nums[] = {30, -23, 1, 11, -3, -8, 7, 0, 31, 13, 25};
    //int nums[] = {1,1,1,1};
    int nums[] = {4,0,5,-5,3,3,0,-4,-5};
    len = ARR_LEN(nums);
    int target = -2;
    printf("target = %d\n", target);
    for (int i=0; i<len; i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");


    // entry point
    threeSumClosest(nums, len, target);
}
