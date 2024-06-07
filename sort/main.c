#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arr.h"

extern void show_quick_sort(int *, int);
extern void show_my_quick_sort(int *, int);
extern void show_bubble_sort(int *, int);
extern void show_insert_sort(int *, int);

int main ()
{
    int *arr;
    int len;

    init_arr(&arr, &len);
    show_arr(arr, len);

    show_bubble_sort(arr, len);
    show_insert_sort(arr, len);
    show_my_quick_sort(arr, len);
    show_quick_sort(arr, len);
}

