#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"

void move_mid(int *mid, int *size, char move_left)
{
    if (move_left) {
        *size = (*size)/2;
        *mid = ((*size) % 2) ? (*mid)-(*size)/2-1: (*mid)-(*size)/2;
    } else {
        *size = ((*size) % 2) ? (*size)/2+1 : (*size)/2;
        *mid = (*mid) + (*size)/2;
    }
}

#define move_leftward(mid, size) ({ \
    size = size/2;                  \
    mid = (size % 2) ? (mid - size/2 -1) : (mid - size/2);  \
})

#define move_rightward(mid, size) ({    \
    size = (size % 2) ? (size/2)+1 : size/2;    \
    mid = mid + size/2;                 \
})

int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int *ret = (int *)malloc(sizeof(int)*2);
    ret[0] = ret[1] = -1;

    // quick return
    if (!numsSize) {
        return ret;
    } else if (nums[0] > target || nums[numsSize-1] < target) {
        return ret;
    }

    int mid = numsSize/2;
    int last_idx = numsSize-1;
    int left_mid, right_mid;    // mid_idx for finding start idx and end_idx
    int left_size, right_size;  // arr size for finding start idx and end idx

    left_mid = right_mid = -1;

    while (ret[0] == -1 || ret[1] == -1) {

        // find common mid such that nums[mid] = target
        if (left_mid == -1) {
            if (target < nums[mid]) {
                move_leftward(mid, numsSize);
            } else if (target > nums[mid]) {
                move_rightward(mid, numsSize);
            }

            if (target == nums[mid]) {  // found common mid
                left_mid = right_mid = mid;
                left_size = right_size = numsSize;
                printf("right_mid = %d, right_size = %d\n", right_mid, right_size);
            }

            if (numsSize == 1) {        // divided arr size is 1, record start/end idx and return
                ret[0] = left_mid;
                ret[1] = right_mid;
                return ret;
            } else {
                continue;   // continue to find common mid first
            }
        }

        // find start idx
        if (ret[0] == -1) {
            if (target == nums[left_mid] && (left_mid == 0 || nums[left_mid-1] < target)) { // found
                ret[0] = left_mid;
            } else {
                if (target <= nums[left_mid]) {
                    move_leftward(left_mid, left_size);
                } else if (target > nums[left_mid]) {
                    move_rightward(left_mid, left_size);
                }
            }
        }

        // find end idx
        if (ret[1] == -1) {
            if (target == nums[right_mid] && (right_mid == last_idx || nums[right_mid+1] > target)) { // found
                ret[1] = right_mid;
            } else {
                if (target >= nums[right_mid]) {
                    move_rightward(right_mid, right_size);
                } else if (target < nums[right_mid]) {
                    move_leftward(right_mid, right_size);
                }
            }
        }
    }

    return ret;
}

#define MIN(a, b) (((a)<=(b)) ? (a) : (b))

int main(int argc, char *argv[])    // arg: len, target_idx, returnSize
{
#if 1
    srand(time(NULL));
    int len, target;
    int target_idx;     // target starts from which idx
    int returnSize;     // how many targets in the arr

    if (argc >= 4) {
        len = strtol(argv[1], NULL, 10);
        target_idx = strtol(argv[2], NULL, 10);
        returnSize = MIN(strtol(argv[3], NULL, 10), len-target_idx);

    } else if (argc >= 3) {
        len = strtol(argv[1], NULL, 10);
        target_idx = strtol(argv[2], NULL, 10);
        returnSize = MIN(rand() % 3, len-target_idx);

    } else if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
        returnSize = rand() % 5;
        target_idx = (returnSize == 0) ? -1 : MIN(rand() % len, len-returnSize);

    } else {
        len = rand() % 10 + 4;
        returnSize = rand() % 5;
        target_idx = (returnSize == 0) ? -1 : MIN(rand() % len, len-returnSize);
    }

    int *arr = (int*) malloc(sizeof(int)*len);
    arr[0] = rand() % 10;
    if (arr[0] % 2)
        arr[0] = -arr[0];
    for (int i=1; i<len; i++) {
        if (target_idx < i && i < target_idx+returnSize) {
            arr[i] = arr[i-1];
        } else {
            arr[i] = arr[i-1] + (rand() % 3) + 1;
        }
    }
    target = (returnSize == 0) ? -1 : arr[target_idx];
#else
    int arr[] = {6,8,9,12};
    int len = 4;
    int target = 12;
    int target_idx = 3;
    int returnSize = 1;
#endif

    arr_show(arr, len);
    printf("target = %d\n", target);
    printf("target idx = %d\n", target_idx);
    printf("returnSize = %d\n", returnSize);

    int ret_size;
    int *ret = searchRange(arr, len, target, &ret_size);

    printf("-------------\n");
    printf("ret  = [%d, %d]\n", ret[0], ret[1]);
}
