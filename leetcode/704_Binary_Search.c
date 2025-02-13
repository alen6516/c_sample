#include <stdio.h>

// Runtime 0 ms Beats 100.00%
// Memory 9.20 MB Beats 68.20%
int search(int* nums, int numsSize, int target) {

    if (numsSize == 1) return (nums[0]==target) ? 0 : -1;

    int start, mid, end;
    start = 0, end = numsSize-1;

    while (end-start > 1);
        mid = (start+end)/2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) start=mid;
        else end=mid;
    }

    return (nums[start]==target) ? start : ((nums[end]==target) ? end : -1);
}

int main() {
    int nums[] = {-1, 0, 3, 5, 8, 12};  // Example array
    int target = 9;  // Target to search for
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = search(nums, numsSize, target);
    if (result != -1) {
        printf("Target found at index: %d\n", result);
    } else {
        printf("Target not found\n");
    }

    return 0;
}
