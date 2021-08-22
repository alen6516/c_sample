/*
Runtime: 28 ms, faster than 34.72% of C online submissions for 3Sum Closest.
Memory Usage: 6.9 MB, less than 100.00% of C online submissions for 3Sum Closest.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(a) ((a)>0 ? (a) : (0-(a)))

int threeSumClosest(int* nums, int numsSize, int target) {

    if(numsSize == 3)
        return nums[0]+nums[1]+nums[2];
    
    int f1, f2, f3;
    int curr;
    int ret = nums[0]+nums[1]+nums[2];
    for (f1 = 0; f1<numsSize-2; f1 ++) {
        for (f2 = f1+1; f2<numsSize-1; f2 ++) {
            for (f3 = f2+1; f3<numsSize; f3 ++) {
                curr = nums[f1]+nums[f2]+nums[f3];
                //printf("f1=%d, f2=%d, f3=%d, curr = %d, abs1 = %d, abs2 = %d\n", f1, f2, f3, curr, abs(curr-target), abs(ret-target));
                if (abs(curr-target) < abs(ret-target) ) {
                    ret = curr;
                }
                if (ret == target) {
                    return ret;
                }
            }
        }
    }

    return ret;
}


int main () {
    int nums[] = {-1, 2, 1, -4};
    int target = 1;
    threeSumClosest(nums, 4, target);

}
