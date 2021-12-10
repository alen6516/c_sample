#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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

    if (nums[start2-1] > target && target > nums[start1]) {
        return search(&nums[start1], start2-start1, target);

    } else if (nums[numsSize-1] > target && target > nums[start2]) {
        return (start2-start1) + search(&nums[start2], numsSize-start2, target);

    } else {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    int len;
    int rotate_idx;
    int target;
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
        target = rand() % len;
    }

    int *arr = (int *) malloc(sizeof(int)*len);
    printf("len = %d, rot_idx = %d, target = %d\n", len, rotate_idx, target);
    printf("arr = [");
    for (int i=0; i<len; i++) {
        arr[i] = (len-rotate_idx+i) % len;
        printf("%d, ", arr[i]);
    }
    printf("]\n");

    printf("idx = %d\n", search(arr, len, target));
}
