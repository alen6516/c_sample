#include <stdio.h>
#include <string.h>
#include <time.h>
#include "arr.h"

void insert_sort(int *arr, int len) {

    int tmp;

    for (int i=1; i<len; i++) {
        for (int j=0; j<i; j++) {
            if (arr[i]<arr[j]) {
                if (i-1 == j) {
                    SWAP(arr[i], arr[j]);
                } else {
                    tmp = arr[i];
                    memmove(&arr[j+1], &arr[j], sizeof(int)*(i-j));
                    arr[j] = tmp;
                }
            }
        }
    } 
}

int main () {

    clock_t start_t, end_t;
    double total_t;


    start_t = clock();
    insert_sort(arr, len);
    end_t = clock();
    total_t = (double) (end_t-start_t)/CLOCKS_PER_SEC;
    print_arr();
    printf("total: %f sec\n", total_t);
}
