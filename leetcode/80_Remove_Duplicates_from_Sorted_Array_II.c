#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 5;
    }

    int *arr1, *arr2;
    arr1 = (int*) malloc(sizeof(int)*len);
    arr2 = (int*) malloc(sizeof(int)*len*3);

    for (int i=0; i<len; i++) {
        if (i == 0) {
            arr1[i] = rand() % 10;
        } else {
            arr1[i] = rand() % 5 + arr1[i-1];
        }
    }

    for (int i=0; i<len; i++) {
        while ()
            arr2[i]
        }
    }
}
