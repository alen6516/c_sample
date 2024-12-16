#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// Runtime 13 ms Beats 76.51% of users with C
// Memory 7.52 MB Beats 83.02% of users with C
// This solution has O(n^2) computation and O(1) space,
// think of a solution with linear computation and O(n) space.
int majorityElement(int* nums, int numsSize) {

    if (numsSize == 1) return nums[0];

    int curr, curr_num;
    int record, record_num = 0;

    // check every number and mark it done
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != '_') {
            curr = nums[i];
            curr_num = 0;

            // find the same number in the remaining arr
            for (int j = i; j < numsSize; j++) {
                if (nums[j] == curr) {
                    curr_num++;
                    nums[j] = '_';
                }
            }
            printf("curr = %d, curr_num = %d\n", curr, curr_num);
            if (curr_num > record_num) {
                record_num = curr_num;
                record = curr;
                printf("new record\n");
            }
        }
    }

    return record;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 5;
    }

    int *arr;
    arr = (int*) malloc(sizeof(int)*len);
    memset(arr, 0, sizeof(int)*len);

    int num = len/2+1;
    int majority = rand() % 10 + 1;

    int i = 0;
    int idx;
    while (i < num) {
        idx = rand() % len;
        if (arr[idx] != majority) {
            arr[idx] = majority;
            i++;
        }
    }

    int j = 0;
    while (j < len) {
        if (arr[j] != majority) {
            arr[j] = majority + (rand() % 20);
        }
        j++;
    }

    arr_show(arr, len);
    printf("majority = %d, num = %d\n", majority, num);

    int ret = majorityElement(arr, len);
    printf("-------------\n");
    printf("ret = %d\n", ret);
    //arr_show(arr, ret);
}
