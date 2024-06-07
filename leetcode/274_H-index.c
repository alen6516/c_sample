// Runtime 0 ms Beats 100.00% of users with C
// Memory 5.70 MB Beats 100.00% of users with C


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

static void
quick_sort_reverse(int *arr, int start, int end)
{
    if (start >= end || start < 0 || end < 0) {
        return;
    }

    int left, right;
    left = start;
    right = end;
    int key = arr[start];

    while(left != right) {
        while(key > arr[right] && left < right) {
            right --;
        }

        while(arr[left] >= key && left < right) {
            left ++;
        }

        if (left < right) {
            SWAP(arr[left], arr[right]);
        }
    }
    SWAP(arr[start], arr[left]);

    quick_sort_reverse(arr, left+1, end);
    quick_sort_reverse(arr, start, left-1);
}

int hIndex(int* citations, int citationsSize) {

    if (citationsSize == 1)
        return (citations[0] > 0);

    // sort arry reversely beforehand
    quick_sort_reverse(citations, 0, citationsSize-1);
    arr_show(citations, citationsSize);

    int ret = citationsSize;
    int count = 0;
    for (int i=0; i < citationsSize; i++) {
        if (citations[i] >= ret)
            count ++;
        else if (citations[i] > count) {
            ret = citations[i];
            count ++;
        } else
            ret = count;

        if (count >= ret)
            break;
    }
    return ret;
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
        len = rand() % 5 + 3;
    }

    arr = arr_create_max(&len, 10, 6);

    arr_show(arr, len);

    ret = hIndex(arr, len);

    printf("h-index: %d\n", ret);
}
