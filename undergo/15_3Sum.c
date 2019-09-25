/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

/*
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){

}
*/


void threeSum(int *nums, int size) {
    

	int f1 = 0;
	int f2 = 1;
	int f3 = 2;

	for (f1 = 0; f1 < size; f1++) { 
        for (f2 = 0; f2 < size && f2 != f1; f2++) { 
            for (f3 = 0; f3 < size && f3 != f2 && f3 != f1; f3++) {
                if (0 == nums[f1]+nums[f2]+nums[f3]) {
                    if (check(f1, f2, f3)) {
                        int *new = (int*) malloc(sizeof(int)*3);
                        new[0] = f1;
                        new[1] = f2;
                        new[2] = f3;
                    }
                } 
            }
        }
    }
}

int main () {

	int nums[] = {1, -2, 1, 1, 0, -1};
	int numsSize = 3;
		

	threeSum(nums, numsSize);
}
