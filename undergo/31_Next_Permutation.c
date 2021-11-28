#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define NUM  10

#define SWAP(a,b) ({        \
    if ((a) != (b)) {       \
        (a) = (a)^(b);      \
        (b) = (a)^(b);      \
        (a) = (a)^(b);      \
    }                       \
})

static void
quick_sort(int *arr, int start, int end)
{
    if (start >= end || start < 0 || end < 0) {
        return;
    }

    int left, right;
    left = start;
    right = end;
    int key = arr[start];

    while(left != right) {
        while(key < arr[right] && left < right) {
            right --;
        }

        while(arr[left] <= key && left < right) {
            left ++;
        }

        if (left < right) {
            SWAP(arr[left], arr[right]);
        }
    }
    SWAP(arr[start], arr[left]);

    quick_sort(arr, left+1, end);
    quick_sort(arr, start, left-1);
}

void nextPermutation(int* nums, int numsSize)
{
    if (numsSize == 1) {
        return;
    } else if (numsSize == 2) {
        SWAP(nums[0], nums[1]);
        return;
    }

    int this, cmp;
    // 3,2,1

    for (cmp = numsSize-2; cmp >= 0; cmp --) {
        this = numsSize-1;
        while (cmp < this) {
            if (nums[cmp] < nums[this]) {
                SWAP(nums[cmp], nums[this]);
                quick_sort(nums, cmp+1, numsSize-1);
                return;
            }
            this --;
        }
    }

    for (int i=0; i<numsSize-1-i; i++) {
        SWAP(nums[i], nums[numsSize-1-i]);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;
    int *arr;
    if (argc > 1) {
        len = argc-1;
        arr = (int*) malloc(sizeof(int)*len);
        for (int i=0; i<len; i++) {
            arr[i] = (int)strtol(argv[i+1], NULL, 10);
        }
    } else {
        len = (rand() % SIZE) + 5;
        arr = (int*) malloc(sizeof(int)*len);
        for (int i=0; i<len; i++) {
            arr[i] = (rand() % NUM);
        }
    }

    printf("len = %d\n", len);
    printf("arr = ");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    nextPermutation(arr, len);

    printf("arr = ");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}
