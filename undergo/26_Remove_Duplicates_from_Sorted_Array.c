#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int removeDuplicates(int* nums, int numsSize){
    int curr, find;
    int val = nums[0];

    curr = 1;
    find = 0;

    while (find < numsSize) {
        if (val == nums[find]) {
            find++;
        } else {
            
        }
    }

}

int main() {
    srand(time(NULL));

    int size = (rand() % 10) + 5;

    int *arr = (int*) malloc(sizeof(int)*size);
    for (int i=0; i<size; i++) {
        if (i==0) {
            arr[i] = rand() % 10;
        } else {
            if (rand() % 2) {
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
}
