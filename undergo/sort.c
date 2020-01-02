#include <stdio.h>
#include <string.h>

#define SWAP(a,b) do {      \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while(0);


void sort(int *arr, int len) {

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


    for (int i=0; i<len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

int main () {

    int arr[] = {2, 1, 4, 9, 8, 6};
    int len = 6;

    sort(arr, len);
}
