#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

void replace_next(int *nums, int size, int k, int i) {

    int tmp;
    int j;
    tmp = nums[i];
    j = (i+k) % size;
    if (j != 0)
        replace_next(nums, size, k, j);
    nums[j] = tmp;
}

void rotate(int* nums, int numsSize, int k) {

    if (numsSize == 1)
        return;

    replace_next(nums, numsSize, k, 0);
}

#if 0
void rotate(int* nums, int numsSize, int k) {

    if (numsSize == 1)
        return;

     k = k % numsSize;
     if (!k) return;


    int last = numsSize-1;
    int tmp;
    while (last != k-1) {
        for (int i=0; i<k; i++) {
            tmp = nums[last-i];
            nums[last-i] = nums[last-i-k];
            nums[last-i-k] = tmp;
        }
        last -= k;
    }
}
#endif

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *arr;
    int len;
    int k;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 5;
    }

    arr = arr_create(&len);
    arr_show(arr, len);

    k = rand() % (len+1);
    printf("k = %d\n", k);
    rotate(arr, len, k);
    printf("-------------\n");
    arr_show(arr, len);
}
