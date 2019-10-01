#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y) {a = a^b; b = a^b; a = a^b;}

int partition(int[], int, int);
void quick_sort(int[], int, int);


int main () {

    int arr[] = {3, 4, 1, 5, 3, 2, 9, -1};

    quick_sort(arr, 0, sizeof(arr)/sizeof(arr[0]));

    for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
        printf("%d\n", arr[i]);
    }

}

int partition (int arr[], int left, int right) {

    int i, j;
    j = left;
    for (j = left; j < right; j++) {
        if (arr[j]<= arr[right]) {
            i
        }
            
    }
}
