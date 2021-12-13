#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define IS_ROTATE(arr, start, end)  (arr[start] > arr[end])

int _search(int* nums, int numsSize, int target)
{
    int start1, start2;
    int ret = 0;
    start1 = 0;

    while (1) {
        start2 = numsSize/2;

        if (nums[start1] == target) {
            //printf("1+%d\n", start1);
            return ret+start1;
        } else if (nums[start2-1] == target) {
            //printf("2+%d\n", start2-1);
            return ret+start2-1;
        } else if (nums[start2] == target) {
            //printf("3+%d\n", start2);
            return ret+start2;
        } else if (nums[numsSize-1] == target) {
            //printf("4+%d\n", numsSize-1);
            return ret+numsSize-1;    
        }

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
            //printf("+%d\n", start2-start1);
        } else if (!IS_ROTATE(nums, start2, (numsSize-1)) &&
            (target > nums[start2] && target < nums[numsSize-1])) {

            nums = &nums[start2];
            numsSize = numsSize-start2;
            ret += (start2-start1);
            //printf("+%d\n", start2-start1);
        } else {
            //printf("-1\n");
            return -1;
        }
    }
}

int search(int* nums, int numsSize, int target)
{
    int start1, start2;
    start1 = 0;
    start2 = numsSize/2;

    if (nums[start1] == target) {
        //printf("1+%d\n", start1);
        return start1;
    } else if (nums[start2-1] == target) {
        //printf("2+%d\n", start2-1);
        return start2-1;
    } else if (nums[start2] == target) {
        //printf("3+%d\n", start2);
        return start2;
    } else if (nums[numsSize-1] == target) {
        //printf("4+%d\n", numsSize-1);
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

        //printf("+%d\n", start2-start1);
        ret = search(&nums[start2], numsSize-start2, target);
        return (ret == -1) ? -1: ret+(start2-start1);
        //return (start2-start1) + search(&nums[start2], numsSize-start2, target);
    } else if (!IS_ROTATE(nums, start2, (numsSize-1)) &&
        (target > nums[start2] && target < nums[numsSize-1])) {

        //printf("+%d\n", start2-start1);
        ret = search(&nums[start2], numsSize-start2, target);
        return (ret == -1) ? -1: ret+(start2-start1);
        //return (start2-start1) + search(&nums[start2], numsSize-start2, target);
    } else {
        //printf("-1\n");
        return -1;
    }
}

int main(int argc, char *argv[])
{
    int len;
    int rotate_idx;
    int target;
    int target_idx;
    srand(time(NULL));

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
        if (argc >= 3) {
            rotate_idx = strtol(argv[2], NULL, 10) % len;
            if (argc >= 4) {
                target = strtol(argv[3], NULL, 10) % len;
            }
        }
    } else {
        len = rand() % 15 + 1;
        rotate_idx = rand() % len;
        target_idx = rand() % len;
    }

    int *arr = (int *) malloc(sizeof(int)*len);
    printf("arr = [");
    for (int i=0; i<len; i++) {
        if (i == rotate_idx) {
            arr[i] == 0;
        } else {
            arr[i] = rand() % 3;
            if (i > 0) {
                arr[i] += arr[i-1];
            }
        }
        if (i == target_idx) {
            if (rand() % 2) {
                target = arr[i];
            } else {
                target = arr[i]-1;
            }
        }
        printf("%d, ", arr[i]);
    }
    printf("]\n");
    printf("len = %d, rot_idx = %d, target = %d\n", len, rotate_idx, target);

    printf("idx = %d\n", _search(arr, len, target));
}
