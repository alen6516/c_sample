#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

int jump(int* nums, int numsSize) {

    if (numsSize == 1) return 0;

    int idx_max = 0;                    // the idx to allow to to max
    int next_idx = idx_max;
    //= idx_max + nums[idx_max];  // max I can reach
    int curr_max;
    int curr_jump = 0;
    int update;

    while(1) {
        curr_max = next_idx+nums[next_idx];
        update = 0;

        printf("start %d, end %d\n", idx_max, curr_max);
        for (int j=idx_max; j<=curr_max; j++) {
            printf("check j = %d ", j);
            if (j+nums[j] >= numsSize-1) {
                printf("find to end\n");
                return (j == 0) ? curr_jump+1 : curr_jump+2;
            } else if (j+nums[j] > next_idx+nums[next_idx]) {
                next_idx = j;
                update = 1;
                printf("update next_max = %d\n", j+nums[next_idx]);
            } else {
                printf("check max = %d, not updated\n", j+nums[j]);
            }

        }

        if (!update) break;


        curr_jump += 1;
        printf("jump to %d, curr_max = %d\n", next_idx, curr_max);
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

    //int arr2[] = {3, 4, 0, 4, 5, 0, 0, 4, 1, 1, 0, 5};
    int arr2[] = {2, 3, 1, 1, 4};
    len = 5;
    arr_show(arr2, len);

    printf("-------------\n");
    ret = jump(arr2, len);
    printf("-------------\n");
    printf("ret = %d\n", ret);
}
