#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "arr.h"

int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{

}

int main(int argc, char *argv[])
{
    srand(time(NULL)) ;
    int len, target, target_idx, returnSize;

    if (argc > 1) {
        len = strtol(argv[1], NULL, 10);
        if (argc > 2) {
            target = strtol(argv[2], NULL, 10);
            if (argc > 3) {
                returnSize = strtol(argv[3], NULL, 10);
            }
        }
    } else {
        len = rand() % 10 + 1;
        target = rand() % 10;
        returnSize = rand() % 3;
    }
    target_idx = rand() % len;

    int arr* = (int*) malloc(sizeof(int)*len);
    for (int i=0; i<len; i++) {
        if (i == 0) {
            arr[i] = rand() % 10;
        } else {
            arr[i] = arr[i-1] + (rand() % 3);
        }
    }

    arr_show(arr, len);
}
