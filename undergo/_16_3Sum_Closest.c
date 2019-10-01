/*
 * Runtime: 28 ms, faster than 34.72% of C online submissions for 3Sum Closest.
 * Memory Usage: 6.9 MB, less than 100.00% of C online submissions for 3Sum Closest.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(a) ((a)>0 ? (a) : (0-(a)))



int threeSumClosest(int* nums, int numsSize, int target) {

    if(numsSize == 3)
        return nums[0]+nums[1]+nums[2];


    
}


int main () {
    int nums[] = {-1, 2, 1, -4};
    int target = 1;
    threeSumClosest(nums, 4, target);

}
