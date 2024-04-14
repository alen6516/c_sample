#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// Runtime 6 ms Beats 98.70% of users with C
// Memory 6.54 MB Beats 54.93% of users with C
int jump(int* nums, int numsSize) {

    if (numsSize == 1) return 0;

    int idx_max = 0;            // the idx to allow me to reach max
    int next_idx = idx_max;     // the next idx allow me to reach max
    int curr_max;               // current max idx I can reach
    int curr_jump = 0;

    while(1) {
        curr_max = next_idx+nums[next_idx];

        // printf("start %d, end %d\n", next_idx, curr_max);
        for (int j=next_idx; j<=curr_max; j++) {
            // printf("check j = %d ", j);
            if (j+nums[j] >= numsSize-1) {
                // find the idx to reach end
                return (j == 0) ? curr_jump+1 : curr_jump+2;
            } else if (j+nums[j] > next_idx+nums[next_idx]) {
                // update next_idx
                next_idx = j;
            }
        }

        curr_jump += 1;
        //printf("jump to %d, curr_max = %d\n", next_idx, curr_max);
    }
    return -1;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *arr;
    int len;
    int ret;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 10;
    }

    arr = arr_create_max(&len, 10, 6);

    arr_show(arr, len);

    printf("-------------\n");
    ret = jump(arr, len);
    printf("-------------\n");
    printf("ret = %d\n", ret);
}
