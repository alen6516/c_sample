/**
 * Description
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// Runtime 101 ms Beats 54.79%
// Memory 8.58 MB Beats 92.56%

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    
    int *ret = (int*) malloc(sizeof(int)*2);

    for (int i=0; i<numsSize-1; i++) {
        for (int j=i+1; j<numsSize; j++) {
            if (nums[i]+nums[j] == target) {
                ret[0] = i;
                ret[1] = j;
                goto out;
            }
        }
    }

out:
    *returnSize = 2;
    return ret;
}
