
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int removeElement(int* nums, int numsSize, int val){

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

    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");

    int target = arr[rand() % len];
    printf("target: %d\n", target);

    int ret_len = removeElement(arr, len, target);

    printf("----------------\n");
    printf("return len: %d\n", ret_len);
    printf("[");
    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}
