#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// 1. move data in nums1 to the right
// 2. get the nth data in nums1 and nums2 to compare and put to the correct position in nums1
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    
    memmove(nums1+n, nums1, m*sizeof(int));
    arr_show(nums1, m+n);

    int to_copy = 0;
    int finished = 0;
    int i = n;
    int j = 0;
    while (finished < nums1Size) {
        while (j < n && nums1[i] >= nums2[j]) {
            to_copy++;
            j++;
        }
        if (to_copy) {
            memcpy(&nums1[finished], &nums2[j-to_copy], to_copy*sizeof(int));
            finished += to_copy;
            printf("copy idx %d number %d from 2 to 1\n", j-to_copy, to_copy);
            to_copy = 0;
        }
        if (j == n) {
            // nums2 are all moved, moving the remaining data in nums1
            //memcpy(&nums1[finished], nums1[])
            break;
        }

        while (i < nums1Size && nums1[i] < nums2[j]) {
            to_copy++;
            i++;
        }
        if (to_copy) {
            memcpy(&nums1[finished], &nums1[i-to_copy], to_copy*sizeof(int));
            finished += to_copy;
            printf("copy idx %d number %d from 1 to 1\n", i-to_copy, to_copy);
            to_copy = 0;
        }
        if (i == m+n) {
            // nums1 are all moved, moving the remaining data in nums2
            memcpy(&nums1[finished], &nums2[j], (n-j)*sizeof(int));
            break;
        }
    }
    
    arr_show(nums1, m+n);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len1, len2;

    if (argc >= 3) {
        len1 = strtol(argv[1], NULL, 10);
        len2 = strtol(argv[2], NULL, 10);

    } else if (argc >= 2) {
        len1 = strtol(argv[1], NULL, 10);

    } else {
        len1 = rand() % 5 + 5;
        len2 = rand() % 5 + 5;
    }

    int *arr1, *arr2;
    arr1 = (int*) malloc(sizeof(int)*(len1+len2));
    arr2 = (int*) malloc(sizeof(int)*len2);

    for (int i=0; i<len1+len2; i++) {
        if (i == 0) {
            arr1[i] = rand() % 10;
        } else if (i >= len1) {
            arr1[i] = 0;
        } else {
            arr1[i] = (rand() % 2) ? arr1[i-1]: (rand() % 5 + arr1[i-1]);
        }
    }

    for (int i=0; i<len2; i++) {
        if (i == 0) {
            arr2[i] = rand() % 10;
        } else {
            arr2[i] = (rand() % 2) ? arr2[i-1]: (rand() % 5 + arr2[i-1]);
        }
    }

    printf("len1 = %d\nlen2 = %d\n", len1, len2);
    arr_show(arr1, len1+len2);
    arr_show(arr2, len2);

    merge(arr1, len1+len2, len1, arr2, len2, len2);
}
