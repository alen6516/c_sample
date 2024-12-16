#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#define move_leftward(mid, size) ({ \
    size = size/2;                  \
    mid = (size % 2) ? (mid - size/2 -1) : (mid - size/2);  \
})

#define move_rightward(mid, size) ({    \
    size = (size % 2) ? (size/2)+1 : size/2;    \
    mid = mid + size/2;                 \
})

int _searchInsert(int* nums, int numsSize, int target) {

    // quick return
    if (numsSize == 1) {
        return (target > nums[0]) ? 1: 0;
    } else if (target <= nums[0]) {
        return 0;
    } else if (target == nums[numsSize-1]) {
        return numsSize-1;
    } else if (target > nums[numsSize-1]) {
        return numsSize;
    }


    int mid = numsSize/2;

    while (numsSize != 1) {
        if (target < nums[mid]) {
            move_leftward(mid, numsSize);
        } else if (target > nums[mid]) {
            move_rightward(mid, numsSize);
        } else {
            return mid;
        }
    }

    return (target > nums[mid]) ? (mid+1) : mid ;
}


// use low and high idx should be faster
// Runtime Details 3ms Beats 69.31%of users with C; Memory Details 6.82MB Beats 17.96%of users with C
int searchInsert(int* nums, int numsSize, int target) {

    // quick return
    if (numsSize == 1) {
        return (target > nums[0]) ? 1: 0;
    } else if (target <= nums[0]) {
        return 0;
    } else if (target == nums[numsSize-1]) {
        return numsSize-1;
    } else if (target > nums[numsSize-1]) {
        return numsSize;
    }

    int low, high;
    low = 0, high = numsSize-1;

    while (high - low > 1) {
        if (target < nums[(low+high)/2]) {
            high = (low+high)/2;
        } else if (target > nums[(low+high)/2]) {
            low = (low+high)/2;
        } else {
            return (low+high)/2;
        }
    }

    return (target > nums[low]) ? (low+1) : low ;
}
#define MIN(a, b) (((a)<=(b)) ? (a) : (b))

int main(int argc, char *argv[])    // arg: len, target_idx
{
#if 1
    srand(time(NULL));
    int len, target;
    int target_idx;     // target starts from which idx

    if (argc >= 3) {
        len = strtol(argv[1], NULL, 10);
        target_idx = strtol(argv[2], NULL, 10);

    } else if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
        target_idx = rand() % len;

    } else {
        len = rand() % 10 + 4;
        target_idx = rand() % len;
    }

    int *arr = (int*) malloc(sizeof(int)*len);
    arr[0] = rand() % 10;
    if (arr[0] % 2)
        arr[0] = -arr[0];
    for (int i=1; i<len; i++) {
        arr[i] = arr[i-1] + (rand() % 3) + 2;
    }

    if (target_idx == 0) {
        target = arr[0];
    } else {
        if (rand() % 2) {
            target = arr[target_idx];
        } else {
            target = (arr[target_idx] + arr[target_idx-1])/2;
        }
    }
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

    int ret_size;
    int ret;

    CLOCK_START();
    ret = _searchInsert(arr, len, target);
    CLOCK_END();
    printf("-------------\n");
    printf("ret_idx = %d, use %f sec\n", ret, CLOCK_DIFF_SEC());

    CLOCK_START();
    ret = searchInsert(arr, len, target);
    CLOCK_END();
    printf("-------------\n");
    printf("ret_idx = %d, use %f sec\n", ret, CLOCK_DIFF_SEC());
}
