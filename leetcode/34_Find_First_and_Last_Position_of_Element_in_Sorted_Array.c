#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "arr.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int *ret = (int*) malloc(sizeof(int)*2);

    // quick return
    if (numsSize == 0 ||
        target > nums[numsSize-1] ||
        target < nums[0]) {
        ret[0] = -1;
        ret[1] = -1;
    }

    int middle;     // idx of the middle
    int *start = nums;

    // 1. continue to chop until find the target
    // 2. from target to find the start and end

    while (numsSize) {
        // 1. find the target

        if (numsSize == 1) {
            // check if it is target or not
            if (nums[0] == target) {
                ret[0] = ret[1] = &nums[0]-start;
            } else {
                ret[0] = ret[1] = -1;
            }
            //return
        } else {
            middle = numsSize/2;
        }

        if (target > nums[middle]) {
            nums = &nums[middle];
            numsSize = numsSize-middle;
        } else if (target < nums[middle]) {
            numsSize = middle;
        } else {
            // nums[middle] is target
            break;
        }
    }

    int *start1 = nums;
    int *start2 = &nums[middle];
    int numsSize1 = start2-start1;
    int numsSize2 = numsSize-middle;

    // find start_idx
    while (numsSize1) {

        if (numsSize1 == 1) {
            // check if it is target or not
            if (start1[0] == target) {
                ret[0] = start1-start;
            } else {
                ret[0] = start2-start;
            }
            break;
        } else {
            middle = numsSize1/2;
        }

        if (target == start1[middle]) {
            numsSize1 = &start1[middle]-start1;
        } else if (target > start1[middle]) {
            start1 = &start1[middle];
            numsSize1 -= middle;
        }
    }

    // find end_idx
    while (numsSize2) {
        
        if (numsSize2 == 1) {
            if (start2[0] == target) {
                ret[1] = start2-start;
            }
            break;
        } else {
            middle = numsSize2/2;
        }

        if (target == start2[middle]) {
            numsSize2 = &start2[middle]-start1;
        } else if (target > start2[middle]) {
            start2 = &start2[middle];
            numsSize2 -= middle;
        }
    }
}

#define MIN(a, b) (((a)<=(b)) ? (a) : (b))

int main(int argc, char *argv[])    // arg: len, target_idx, returnSize
{
    srand(time(NULL)) ;
    int len, target, target_idx, returnSize;

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
    for (int i=1; i<len; i++) {
        if (target_idx < i && i < target_idx+returnSize) {
            arr[i] = arr[i-1];
        } else {
            arr[i] = arr[i-1] + (rand() % 3) + 1;
        }
    }
    target = (returnSize == 0) ? -1 : arr[target_idx];

    arr_show(arr, len, 0);
    printf("target = %d\n", target);
    printf("target idx = %d\n", target_idx);
    printf("returnSize = %d\n", returnSize);

    int ret_size;
    int ret_idx = searchRange(arr, len, target, &ret_size); 

    printf("-------------\n");
    printf("ret_idx  = %d\n", ret_idx);
    printf("ret_size = %d\n", ret_size);
}
