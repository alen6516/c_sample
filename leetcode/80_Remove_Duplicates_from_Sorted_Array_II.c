// Runtime 7 ms Beats 85.57% of users with C
// Memory 6.24 MB Beats 94.64% of users with C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

int removeDuplicates(int* nums, int numsSize) {

    if (numsSize < 3) return numsSize;

    int curr = 2;   // idx of current
    int find;       // idx to find a proper element
    int done = 1;   // idx that we've finished processing

    while (curr < numsSize) {
        if (nums[done-1] == nums[done] && nums[done] == nums[curr]) {
            // if 3 consecutive same elements, find a proper element and copy it to done's next
            find = curr;
            while (find < numsSize && nums[curr] == nums[find]) {
                find++;

                if (find == numsSize) return done+1;
            }
            done++;
            nums[done] = nums[find];
            curr = find+1;
        } else if (curr != done+1) {
            // no 3 consecutive elements but curr is far from done, copy curr to done's next
            done++;
            nums[done] = nums[curr];
            curr++;
        } else {
            done++;
            curr++;
        }
    }

    return done+1;
}

#define MAX_CONSECUTIVE_NUM 3

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 5;
    }

    int *arr1, *arr2;
    arr1 = (int*) malloc(sizeof(int)*len);
    arr2 = (int*) malloc(sizeof(int)*len*MAX_CONSECUTIVE_NUM);

    int inc;
    for (int i=0; i<len; i++) {
        inc = rand() % 3;
        if (i == 0) {
            arr1[i] = inc;
        } else if (i > 1 && arr1[i-2] == arr1[i-1]) {
            arr1[i] = arr1[i-1] + inc + 1;
        } else {
            arr1[i] = arr1[i-1] + inc;
        }
    }
    arr_show(arr1, len);

    int rep;
    int len2 = 0;
    for (int i=0; i<len; i++) {
        if (i > 0 && arr1[i-1] == arr1[i]) {
            rep = (rand() % MAX_CONSECUTIVE_NUM) + 1;
        } else {
            rep = 1;
        }
        while (rep) {
            arr2[len2] = arr1[i];
            len2++;
            rep--;
        }
    }
    arr_show(arr2, len2);

    int ret = removeDuplicates(arr2, len2);
    printf("-------------\n");
    printf("ret = %d\n", ret);
    arr_show(arr2, ret);
}
