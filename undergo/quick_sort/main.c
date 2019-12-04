#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int arr[] = {3, 4, 1, 5, 3, 2, 9, -1};

void print_arr() {
    for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

#define SWAP(a, b)                          \
    do {                                    \
        printf("swap %d and %d\n", a, b);   \
        a = a^b;                            \
        b = a^b;                            \
        a = a^b;                            \
        print_arr();                        \
    } while (0)

int partition(int[], int, int);
void quick_sort(int[], int, int);


int main () {
    
    print_arr();
    quick_sort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    print_arr();
}

int partition (int arr[], int left, int right) {

    /*
    if (left == right-1) {
        if (arr[left] > arr[right])
            SWAP(arr[left], arr[right]);
        return 0;
    }
    */

    int mid_idx = right;
    right--;
    int swap_with_mid_before_return = -1;


    for (;left <= right; left++) {
        if (arr[left] > arr[mid_idx]) {     // if this one is larger then mid

            swap_with_mid_before_return = left;

            // find a small one from right
            for (; right > left ; right--) {
                if (arr[right] < arr[mid_idx]) {

                    // if find, then swap them
                    SWAP(arr[left], arr[right]);
                    swap_with_mid_before_return = right;
                    break;
                }
            }
        } 
    }

    if (swap_with_mid_before_return != -1) {
        SWAP(arr[swap_with_mid_before_return], arr[mid_idx]);
        return swap_with_mid_before_return;
    } else {
        return right;
    }
}

void quick_sort(int arr[], int left, int right) {

    int q;

    printf("left = [%d], right = [%d]\n", left, right);
    q = partition(arr, left, right);
    
    if (q != left && q != left+1)
        quick_sort(arr, left, q-1);
    if (q != right && q != right-1)
        quick_sort(arr, q+1, right);
}

