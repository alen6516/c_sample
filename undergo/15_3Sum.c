/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>


/*
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){

}
*/

int min(int a, int b, int c) {

    return (a>b) ? ( (b>c) ? c: b ) : ( (a>c) ? c: a);
}

#define MIN_3(a, b, c) ((a>b) ? ( (b>c) ? c : b ) : ( (a>c) ? c : a))


int arr_1[10];
int arr_2[10];
int arr_3[10];

void threeSum(int *nums, int size) {
    
	int f1;
	int f2;
	int f3;

	for (f1 = 0; f1 < size; f1++) { 
        for (f2 = f1+1; f2 < size; f2++) { 
            for (f3 = f2+1; f3 < size; f3++) {
                if (0 == nums[f1]+nums[f2]+nums[f3]) {
                    
                    /*
                    if (check(f1, f2, f3)) {
                        int *new = (int*) malloc(sizeof(int)*3);
                        new[0] = f1;
                        new[1] = f2;
                        new[2] = f3;
                    }
                    */
                    printf("f1=%d:%d, f2=%d:%d, f3=%d:%d\n", f1, nums[f1], f2, nums[f2], f3, nums[f3]);
                    
                } 
            }
        }
    }
}

int main () {

	int nums[] = {1, -2, 1, 1, 0, -1};
	printf("{1, -2, 1, 1, 0, -1}\n");
	int numsSize = 6;
		

	threeSum(nums, numsSize);
}
