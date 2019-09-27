/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){

}
*/

#define MIN_3(a, b, c) ((a>b) ? ( (b>c) ? c : b ) : ( (a>c) ? c : a))
#define MAX_3(a, b, c) ((a<b) ? ( (b<c) ? c : b ) : ( (a<c) ? c : a))

#define c_size_get_2(size) size*(size-1)/2


int get_idx(int input, int *arr, int total) {
    for (int i=0; i<total; i++) {
        if (arr[i] == input) {
            return i;
        }
    }
    return -1;
}


void threeSum(int *nums, int size) {
    
	int f1;
	int f2;
	int f3;


    int this_max, this_min;

    int tmp_idx;

    int total = 0;
    int arr_min[c_size_get_2(size)];
    int arr_max[c_size_get_2(size)];

	for (f1 = 0; f1 < size; f1++) { 
        for (f2 = f1+1; f2 < size; f2++) { 
            for (f3 = f2+1; f3 < size; f3++) {
                if (0 == nums[f1]+nums[f2]+nums[f3]) {
                    
                    this_max = MAX_3(nums[f1], nums[f2], nums[f3]);
                    this_min = MIN_3(nums[f1], nums[f2], nums[f3]);


                    tmp_idx = get_idx(this_min, arr_min, total);
                    if (tmp_idx != -1 && arr_max[tmp_idx] == this_max) {
                        // ignore
                    } else {
                        arr_min[total] = this_min;
                        arr_max[total] = this_max;
                        total++;

                        printf("min=%d, med=%d, max=%d\n", this_min, 0-this_max-this_min, this_max);
                    }
                } 
            }
        }
    }
}

int main () {

	int nums[] = {1, -2, 1, -5, 1, 0, -1, -2, 4, 3};
	printf("{1, -2, 1, -5, 1, 0, -1, -2, 4, 3}\n");
	int numsSize = 10;
		
	threeSum(nums, numsSize);
}
