#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 20

void show(int arr[]) {
    for (int i=0; i<LEN; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void compress(int arr[]) {
    int eid = LEN-1;
    for (int i=0; i<eid; i++) {
        if (arr[i] == 0) {
            for (; eid>i; eid--) {
                if (arr[eid] != 0) {
                    arr[i] = arr[eid];
                    arr[eid] = 0;
                    break;
                }
            }
        }
    }
}


int main () {

    int arr[LEN];
    srand(time(NULL));
    for (int i=0; i<LEN; i++) {
        arr[i] = rand() % 5;
    }
    show(arr);
    compress(arr);
    show(arr);
}
