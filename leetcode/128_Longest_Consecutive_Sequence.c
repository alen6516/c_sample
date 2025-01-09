/**
 * Description
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#define ARR_SIZE(arr) (int)sizeof(arr)/sizeof(arr[0])

#define SWAP(a, b) do {     \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while (0)

// O(n^2) way:
// [0, 3, 6, 2, 1, 7]
// max = min = arr[0], go through arr to find if there is max+1 or min-1
// once 1 round finished, if max or min is updated, continue to go next round for i=0
// if this round max and min is not update, max = min = arr[1] from step 1 again
int longestConsecutive(int* nums, int numsSize) {

    int max, min, len;
    int j1, j2;
    int max_id, min_id;
    len = 1;

    int i=0;
    for (; i<numsSize; i++) {
        max = min = nums[i];
        
        for(int j=0; j<numsSize; j++) {
            if (nums[j] == max+1) {
                max++;
                j1 = j; // debug
                j=0;
            } else if (nums[j] == min-1) {
                min--;
                j2 = j; // debug
                j=0;
            }
        }
        if (max-min+1 > len) {
            len = max-min+1;
            max_id = j1;
            min_id = j2;
        }
    }

    printf("len = %d, max_id = %d, min_id = %d\n", len, max_id, min_id);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    }
}
