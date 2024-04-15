#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

int hIndex(int* citations, int citationsSize) {

    int ret = citationsSize;
    for (int i=0; i<citationsSize; i++) {
        if ()
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *arr;
    int len;
    int ret;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 5;
    }

    arr = arr_create_max(&len, 10, 6);

    arr_show(arr, len);

}
