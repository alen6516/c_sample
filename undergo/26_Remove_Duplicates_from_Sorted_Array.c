
/*
Solution: start from the end of the array and detect duplicate numbers,
once found, memmove to overrite the duplicated one.

4 5 6 7 8 9 9 9 9 1 2 3
                |<--->|
          9 1 2 3
          |<--->|  memmove
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 6, 7, 7, 7, 7, 9, 9, 9, 16, 20

int removeDuplicates(int* nums, int numsSize){
    if (numsSize == 0 || numsSize == 1) return numsSize;

    int size = 1;
    int flag = 0; // 0 means still finding src, 1 means finding dst
    int *src, *dst;
   
    for (int i=numsSize-2; i>=0; i--) {
        if (nums[i] == nums[i+1]) {
            if (!flag) {
                src = &nums[i+1];
                size ++;
                flag = 1;
            } 
            if (i == 0 && flag) {
                //printf("before, size %d, src = %ld, dst = %ld\n", size, (src-nums), (dst-nums));
                memcpy(nums, src, size*sizeof(int));
                break;
            }
        } else {
            if (flag) {
                dst = &nums[i+1];
                //printf("before, size %d, src = %ld, dst = %ld\n", size, (src-nums), (dst-nums));
                memcpy(dst, src, size*sizeof(int));
                flag = 0;
            } else {
                size++;
            }
        }
    }
    return (size == 0) ? numsSize : size;
}


int _removeDuplicates(int* nums, int numsSize){
    if (numsSize == 0 || numsSize == 1) return numsSize;
    int curr = nums[0];
    int *rp = NULL;
    for (int i=1; i<numsSize; i++) {
        if (nums[i] == curr) {
            if (!rp) rp = &nums[i];
        } else {
            if (rp) {
                *rp = nums[i];
                rp += 1;
            }
            curr = nums[i];
        }
    }
    return (rp) ? ((rp-nums)): numsSize;
}

int main() {
    srand(time(NULL));

    int size = (rand() % 100) + 5;

    // create arr
    int *arr = (int*) malloc(sizeof(int)*size);
    for (int i=0; i<size; i++) {
        if (i==0) {
            arr[i] = rand() % 10;
        } else {
            if (rand() % 5) {
                arr[i] = arr[i-1]+(rand() % 10);
            } else {
                arr[i] = arr[i-1];
            }
        }
    }

    printf("arr size = %d\n", size);
    for (int i=0; i<size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    int *arr2 = (int*) malloc(sizeof(int)*size);
    memcpy(arr2, arr, size*sizeof(int));


    clock_t start, end, diff1, diff2;
    int ret_len;

    //start = clock();
    //ret_len = removeDuplicates(arr, size);
    //end = clock();
    //for (int i=0; i < ret_len; i++) {
    //    printf("%d, ", arr[i]);
    //}
    //printf("\n");
    //diff1 = end-start;
    //printf("spend clock %ld, sec %f\n", end-start, (float)(end-start)/CLOCKS_PER_SEC);

    //start = clock();
    //ret_len = _removeDuplicates(arr2, size);
    //end = clock();
    //for (int i=0; i < ret_len; i++) {
    //    printf("%d, ", arr[i]);
    //}
    //printf("\n");
    //diff2 = end-start;
    //printf("spend clock %ld, sec %f\n", end-start, (float)(end-start)/CLOCKS_PER_SEC);

    free(arr);
    free(arr2);
}
