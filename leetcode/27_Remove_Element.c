/*
Runtime: 0 ms, faster than 100.00% of C online submissions for Remove Element.
Meomory Usage: 6.1 MB, less than 50.19% of C online submissions for Remove Element.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// start from tail, find a replacement first, later if find a target then replace it.
int removeElement(int *nums, int numsSize, int val)
{
    if (!numsSize) return 0;
    int replace = -1;
    while ((--numsSize) >= 0) {
        if (replace == -1) {
            // find replacement from tail
            if (nums[numsSize] != val) {
                replace = numsSize;
            }
        } else if (nums[numsSize] == val) {
            // if replacement is set, then 
            nums[numsSize] = nums[replace];
            //nums[replace] = -1;
            replace--;
        }
    }
    return (replace == -1) ? 0 : (replace+1);
}


// Find the target from the head of array, and replace it
// with another value found from the end of array.
int _removeElement(int* nums, int numsSize, int val){
    if (!numsSize) return 0;

    int head, tail;
    head = -1, tail = numsSize-1;
    while(head < tail) {
        head++;
        if (nums[head] == val) {
            while(head < tail) {
                if (nums[tail] == val) {
                    tail--;
                } else {
                    nums[head] = nums[tail];
                    nums[tail] = -1;
                    tail--;
                    break;
                }
            }
        }
    }

    return (nums[head]==val) ? head : (head+1);
}

int main ()
{
    
    srand(time(NULL));
    int len = (rand() % 10) + 5;
    int *arr = (int*) malloc(sizeof(int)*len);
    printf("len = %d\n", len);

    for (int i=0; i<len; i++) {
        if (rand() % 3 == 0 && i != 0) {
            arr[i] = arr[(rand() % i)];  
        } else {
            arr[i] = rand() % 10;
        }
    }

    int *arr2 = (int*) malloc(sizeof(int)*len);
    memcpy(arr2, arr, sizeof(int)*len);

    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");

    int target = arr[rand() % len];
    printf("target: %d\n", target);

    int ret_len;
    clock_t start, end;

    start = clock();
    ret_len = removeElement(arr, len, target);
    end = clock();

    printf("----- method 1 ------\n");
    printf("return len: %d\n", ret_len);
    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
    printf("spend clock %ld, sec %f\n", (end-start), (float)(end-start)/CLOCKS_PER_SEC);


    start = clock();
    ret_len = _removeElement(arr2, len, target);
    end = clock();

    printf("----- method 2 -----\n");
    printf("return len: %d\n", ret_len);
    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
    printf("spend clock %ld, sec %f\n", (end-start), (float)(end-start)/CLOCKS_PER_SEC);
}
