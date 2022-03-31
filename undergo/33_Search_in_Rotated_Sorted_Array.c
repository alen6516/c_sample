/*
 There is an integer array nums sorted in ascending order (with distinct values).
 
 Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
 
 Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 
 You must write an algorithm with O(log n) runtime complexity.
 
  
 Example 1:
 Input: nums = [4,5,6,7,0,1,2], target = 0
 Output: 4

 Example 2:
 Input: nums = [4,5,6,7,0,1,2], target = 3
 Output: -1

 Example 3:
 Input: nums = [1], target = 0
 Output: -1
  
 Constraints:
 1 <= nums.length <= 5000
 -104 <= nums[i] <= 104
 All values of nums are unique.
 nums is an ascending array that is possibly rotated.
 -104 <= target <= 104
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define IS_ROTATE(arr, start, end)  (arr[start] > arr[end])

/**
 * Use loop to narrow down the scope.
 * Cut the array in the middle, first part starts with start1, second part start with start2.
 */
int _search(int* nums, int numsSize, int target)
{
    int start1, start2;
    int ret = 0;
    start1 = 0;

    while (1) {
        /* cut the array in the middle */
        start2 = numsSize/2;

        /* check and return */
        if (nums[start1] == target) {
            return ret+start1;
        } else if (nums[start2-1] == target) {
            return ret+start2-1;
        } else if (nums[start2] == target) {
            return ret+start2;
        } else if (nums[numsSize-1] == target) {
            return ret+numsSize-1;    
        }

        /*
         * Check which segment rotating occurs and if target is in
         * that segment.
         */
        if (IS_ROTATE(nums, start1, (start2-1)) &&
            (target > nums[start1] || target < nums[start2-1])) {

            nums = &nums[start1];
            numsSize = start2-start1;
        } else if (!IS_ROTATE(nums, start1, (start2-1)) &&
            (target > nums[start1] && target < nums[start2-1])) {

            nums = &nums[start1];
            numsSize = start2-start1;
        } else if (IS_ROTATE(nums, start2, (numsSize-1)) &&
            (target > nums[start2] || target < nums[numsSize-1])) {

            nums = &nums[start2];
            numsSize = numsSize-start2;
            ret += (start2-start1);
        } else if (!IS_ROTATE(nums, start2, (numsSize-1)) &&
            (target > nums[start2] && target < nums[numsSize-1])) {

            nums = &nums[start2];
            numsSize = numsSize-start2;
            ret += (start2-start1);
        } else {
            return -1;
        }
    }
}

/**
 * narrow down the scope by recursion
 */
int search(int* nums, int numsSize, int target)
{
    int start1, start2;
    start1 = 0;
    start2 = numsSize/2;

    if (nums[start1] == target) {
        return start1;
    } else if (nums[start2-1] == target) {
        return start2-1;
    } else if (nums[start2] == target) {
        return start2;
    } else if (nums[numsSize-1] == target) {
        return numsSize-1;    
    }

    int ret;
    if (IS_ROTATE(nums, start1, (start2-1)) &&
        (target > nums[start1] || target < nums[start2-1])) {

        return search(&nums[start1], start2-start1, target);
    } else if (!IS_ROTATE(nums, start1, (start2-1)) &&
        (target > nums[start1] && target < nums[start2-1])) {

        return search(&nums[start1], start2-start1, target);
    } else if (IS_ROTATE(nums, start2, (numsSize-1)) &&
        (target > nums[start2] || target < nums[numsSize-1])) {

        ret = search(&nums[start2], numsSize-start2, target);
        return (ret == -1) ? -1: ret+(start2-start1);
    } else if (!IS_ROTATE(nums, start2, (numsSize-1)) &&
        (target > nums[start2] && target < nums[numsSize-1])) {

        ret = search(&nums[start2], numsSize-start2, target);
        return (ret == -1) ? -1: ret+(start2-start1);
    } else {
        return -1;
    }
}

int main(int argc, char *argv[])    // arg: len, rotate_idx, target_idx
{
    int len;
    int rotate_idx;
    int target_idx;
    int target;
    srand(time(NULL));

    if (argc >= 4) {
        len = strtol(argv[1], NULL, 10);
        rotate_idx = strtol(argv[2], NULL, 10) % len;
        target_idx = strtol(argv[3], NULL, 10) % len;

    } else if (argc >= 3) {
        len = strtol(argv[1], NULL, 10);
        rotate_idx = strtol(argv[2], NULL, 10) % len;
        target_idx = rand() % len;

    } else if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
        rotate_idx = rand() % len;
        target_idx = rand() % len;

    } else {
        len = rand() % 15 + 1;
        rotate_idx = rand() % len;
        target_idx = rand() % len;
    }

    int *arr = (int *) malloc(sizeof(int)*len);
    arr[rotate_idx] = 0;
    for (int i=1, idx; i<len; i++) {
        idx = (rotate_idx+i) % len;

        // current = prev + rand()%3
        arr[idx] = arr[(idx+len-1) % len] + (rand() % 3);

        if (idx == target_idx) {
            if (rand() % 2) {
                // target is in the array
                target = arr[idx];
            } else {
                target = arr[idx]-1;
            }
        }
    }

    printf("arr = [%d", arr[0]);
    for (int i=1; i<len; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n");

    printf("len = %d, rot_idx = %d, target = %d\n", len, rotate_idx, target);

    printf("idx = %d\n", _search(arr, len, target));
}
