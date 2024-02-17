#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#ifdef alan

#define SWAP(a, b)  \
    a = a^b;        \
    b = a^b;        \
    a = a^b;

void rotate(int* nums, int numsSize, int k) {

    if (numsSize == 1)
        return;

    if (!k) return;

    int done = k;
    int start_idx = 0;
    int start_val = nums[0];
    int tmp = nums[0];
    int i = 0;
    while (done != 0) {
        i += k;
        if (i < numsSize) {
            SWAP(tmp, nums[i]);
        } else {
            i -= numsSize;
            SWAP(tmp, nums[i]);
            done --;
            if (start_idx == i) {
                i++;
            }
        }
    }
}
#else

void rotate(int* nums, int numsSize, int k) {

    if (numsSize == 1)
        return;

    k = k % numsSize;
    if (!k) return;

    int *tmp;

    if (k <= numsSize/2) {
        tmp = malloc(sizeof(int)*k);
        for (int i=0; i<k; i++) {
            tmp[i] = nums[numsSize-k+i];
        }
        for (int i=0; i<numsSize-k; i++) {
            nums[numsSize-1-i] = nums[numsSize-1-k-i];
        }
        for (int i=0; i<k; i++) {
            nums[i] = tmp[i];
        }
    } else {
         k = numsSize-k;
         tmp = malloc(sizeof(int)*k);
         for (int i=0; i<k; i++) {
            tmp[i] = nums[i];
         }
         for (int i=0; i<numsSize-k; i++)
            nums[i] = nums[i+k];

         for (int i=0; i<k; i++)
            nums[numsSize-k+i] = tmp[i];
    }

    free(tmp);
}
#endif

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *arr;
    int len;
    int k;

    if (argc >= 3) {
        len = strtol(argv[1], NULL, 10);
        k = strtol(argv[2], NULL, 10);
    } else if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
        k = rand() % (len+1);
    } else {
        len = rand() % 5 + 5;
        k = rand() % (len+1);
    }

    arr = arr_create(&len);
    arr_show(arr, len);

    printf("k = %d\n", k);
    rotate(arr, len, k);
    printf("-------------\n");
    arr_show(arr, len);
}
