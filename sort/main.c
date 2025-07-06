#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../utils/arr.h"

extern void show_quick_sort(int *, int);
extern void show_my_quick_sort(int *, int);
extern void show_oop_quick_sort(int *, int);
extern void show_bubble_sort(int *, int);
extern void show_insert_sort(int *, int);
extern void show_selection_sort(int *, int);

int main()
{
    int *arr;
    int len;

    arr = arr_create_random(&len);
    arr_show(arr, len);

    //show_bubble_sort(arr, len);
    //show_insert_sort(arr, len);
    //show_my_quick_sort(arr, len);
    show_quick_sort(arr, len);
    //show_oop_quick_sort(arr, len);
    //show_selection_sort(arr, len);
}

