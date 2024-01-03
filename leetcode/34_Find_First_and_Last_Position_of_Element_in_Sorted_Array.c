#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int *ret = (int *)malloc(sizeof(int)*2);

    if (target < 0) {
        ret[0] = ret[1] = -1;
        return ret;
    }

    int mid;
    mid = numsSize/2;

    while (!(nums[mid] == target && nums[mid-1] < target)) {

        if (target <= nums[mid]) {  // target is in the left side

            // decide next mid idx
            numsSize = numsSize/2;
            if (numsSize % 2)
                mid = mid - numsSize/2 -1;
            else
                mid = mid - numsSize/2;
        } else {                    // target is in the right side

            // decide next mid idx
            numsSize = (numsSize % 2) ? (numsSize/2)+1 : numsSize/2;
            if (numsSize % 2)
                mid = mid + numsSize/2;
            else
                mid = mid + numsSize/2;
        }
    }
    printf("%d, %d\n", nums[mid-1], nums[mid]);
    return &nums[mid-1];
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

    arr_show(arr, len);
    printf("target = %d\n", target);
    printf("target idx = %d\n", target_idx);
    printf("returnSize = %d\n", returnSize);

    int ret_size;
    int *ret_idx = searchRange(arr, len, target, &ret_size);

    printf("-------------\n");
    printf("ret_idx  = [%d, %d]\n", ret_idx[0], ret_idx[1]);
}
