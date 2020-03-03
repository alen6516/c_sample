#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) do {     \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while (0);


int arr[] = {3, 4, 1, 5, 3, 2, 9, -1, 20,19,18,17,16,15, 14, 13, 12, 11};
int len = sizeof(arr)/sizeof(int);

void print_arr() {
   for (int i=0; i<len; i++) {
    printf("%d, ", arr[i]);
   }
   printf("\n");
}


#endif
