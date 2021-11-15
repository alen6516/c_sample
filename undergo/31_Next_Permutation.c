#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

#define SWAP(a,b) do {  \
    a = a^b;            \
    b = a^b;            \
    a = a^b;            \
} while(0);

void nextPermutation(int* nums, int numsSize)
{
    if (numsSize == 1) {
        return;
    } else if (numsSize == 2) {
        SWAP(nums[0], nums[1]);
        return;
    }

    unsigned int this, cmp;
    // 3,2,1

    for (cmp = numsSize-2; cmp >= 0; cmp --) {
        this = numsSize-1;
        while (cmp < this) {
            if (nums[cmp] < nums[this]) {
                SWAP(nums[cmp], nums[this]);
                return;
            }
            this --;
        }
    }
}

int main()
{
    srand(time(NULL));
    int len = (rand() % SIZE) + 5;
    int *arr = (int*) malloc(sizeof(int)*len);
    for (int i=0; i<len; i++) {
        arr[i] = (rand() % SIZE);
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
