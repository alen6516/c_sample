#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#ifdef alan

/*
#define SWAP(a, b)  \
    a = a^b;        \
    b = a^b;        \
    a = a^b;
*/

/* rotate from the 1st number
 * 1 -> 1+k
 * 1+k -> 1+2k
 * ...
 * When wrap around, if wrap around to original start idx, then start from the next idx
 * In this way we can process all number in array when we process all first k numbers
 * In most case, we don't need to change start idx, but in case like below we need:
 * (arr_size, k) = (6, 4), (6, 3)
 */
// Runtime 93 ms Beats 89.55% of users with C
// Memory 21.67 MB Beats 99.64% of users with C
void rotate(int* nums, int numsSize, int k) {

    if (numsSize == 1) return;
    k = k % numsSize;
    if (!k) return;

    int done = 0;       // in first k numbers, how many are rotated
    int start_idx = 0;  // now start from this idx in the first k number
    int tmp = nums[0];  // value to be rotated
    int i = 0;
    while (done != k) {             // while not all first k numbers are done
        i += k;
        if (i < numsSize) {
            SWAP(tmp, nums[i]);
        } else {                    // if wrap around
            i -= numsSize;
            SWAP(tmp, nums[i]);
            done ++;
            if (start_idx == i) {   // if wrap around to the original start idx, start from the next idx
                i++;
                tmp = nums[i];
                start_idx = i;
            }
        }
    }
}
#else

// Runtime 94 ms Beats 87.70% of users with C
// Memory 22.11 MB Beats 65.31% of users with C
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
