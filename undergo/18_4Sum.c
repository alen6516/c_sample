

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
    
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE(arr) (int)sizeof(arr)/sizeof(arr[0])

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){

	printf("nums = [");
	for (int i=0; i<numsSize; i++) {
		printf("%d, ", nums[i]);
	}
	printf("]\n");

	printf("target = %d\n", target);
	return NULL;
}


int main () {

	int nums[] = {1, 0, -1, 0, -2, 2};
	int target = 0;

	int **ret;
	int returnSize;
	int *returnColumnSizes;
	ret = fourSum(nums, ARR_SIZE(nums), target, &returnSize, &returnColumnSizes);
	
}
