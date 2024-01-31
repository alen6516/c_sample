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
    
    // move data in nums1 to right
    for (int i=0; i < m; i++) {
        nums1[nums1Size-i-1] = nums1[m-i-1];
        nums1[m-i-1] = 0;
    }
    arr_show(nums1, m+n);

    int to_copy = 0;
    int finished = 0;
    int i = n;
    int j = 0;
    while (finished < nums1Size) {
        // find datas in nums2 and copy to nums1
        while (j < n && nums1[i] >= nums2[j]) {
            to_copy++;
            j++;
        }
        while (to_copy > 0) {
            nums1[finished] = nums2[j-to_copy];
            //printf("copy idx %d number %d from 2 to 1\n", j-to_copy, to_copy);
            to_copy--;
            finished++;
        }

        if (j == n) {
            // nums2 are all moved, moving the remaining data in nums1
            //memcpy(&nums1[finished], nums1[])
            break;
        }

        // find datas in nums1 and copy to nums1
        while (i < nums1Size && nums1[i] < nums2[j]) {
            to_copy++;
            i++;
        }
        while (to_copy > 0) {
            nums1[finished] = nums1[i-to_copy];
            //printf("copy idx %d number %d from 2 to 1\n", j-to_copy, to_copy);
            to_copy--;
            finished++;
        }
        if (i == m+n) {
            // nums1 are all moved, moving the remaining data in nums2
            while (j < n) {
                nums1[finished] = nums2[j];
                j++;
                finished++;
            }
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
