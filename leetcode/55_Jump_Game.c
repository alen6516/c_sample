#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// Runtime 46 ms Beats 75.87% of users with C
// Memory 7.91 MB Beats 93.57% of users with C
bool canJump(int* nums, int numsSize) {

    int max = 0;
    for (int i=0; i<numsSize; i++) {

        // update max
        if (i+nums[i] > max)
            max = i+nums[i];

        if (max >= numsSize-1)  // check if can jump to end
            return true;
        else if (i == max)      // break if can't continue
            return false;
    }
    return false;
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

    arr = arr_create_max(&len, 10, 4);
    arr_show(arr, len);

    ret = canJump(arr, len);
    printf("-------------\n");
    printf("ret = %s\n", ret ? "yes" : "no");
}
