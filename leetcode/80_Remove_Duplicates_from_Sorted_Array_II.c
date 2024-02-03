#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

int removeDuplicates(int* nums, int numsSize) {

    int rep = 0;        // how many repeats now
    int i = 0;          // current processed idx
    int prev;

    while (i < numsSize) {
        if (i > 0 && numsSize[i-1] == numsSize[i]) {
            prev =  numsSize[i];
        }

        if (rep == 2) {
            if (!find_idx)
                find_idx = i+1;
            while (numsSize[i] == numsSize[find_idx]) {
                find_idx++;
                if (find_idx == numsSize)
                    return i-1;
            }
            numsSize[i] = numsSize[find_idx];
            rep = 0;
        }

        i++;
    }

    return i;

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
