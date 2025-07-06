#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef fail     // fail due to execution time out
// maintain an array to track the first-k largerst element
// len: current array len
// size: array size
void insert_to_arr(int *arr, int *len, int size, int val)
{
    int i=0;
    for (; i < (*len); i++) {
        if (val >= arr[i]) {
            break;
        }
    }

    if (i < size) {     // if array not full, need to insert or append
        if (i < *len) { // need to memmove and insert
            memmove(&arr[i+1], &arr[i], sizeof(int)*(size-i-1));
        }
        arr[i] = val;
        if (*len < size) (*len)++;
    }
}

int findKthLargest(int* nums, int numsSize, int k) {

    int *arr = (int*) malloc(sizeof(int)*k);
    int len = 0;
    int ret;
    //memset(arr, 0, sizeof(int)*k);

    for (int i=0; i<numsSize; i++) {
        insert_to_arr(arr, &len, k, nums[i]);
    }

    ret = arr[k-1];
    free(arr);
    return ret;
}

#else
// bheap sort beforehand



#endif

int main()
{
    int arr[] = {1,0,6,2,5,8};
    int len = 6;

    int ret;
    ret = findKthLargest(arr, 6, 4);
    printf("%d\n", ret);
}
