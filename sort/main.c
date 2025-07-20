#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../utils/arr.h"

extern void show_quick_sort(int *, int);
extern void show_my_quick_sort(int *, int);
extern void show_bheap_sort(int *, int);
extern void show_my_bheap_sort(int *, int);
//extern void show_oop_quick_sort(int *, int);
extern void show_bubble_sort(int *, int);
extern void show_insert_sort(int *, int);
extern void show_selection_sort(int *, int);

clock_t __start, __end;

int main(int argc, char *argv[])
{
    int *arr, len;
    if (argc > 1)
        len = (int) strtol(argv[1], NULL, 10);

    arr = arr_create_random(&len);
    arr_show(arr, len);

    //show_bubble_sort(arr, len);
    //show_insert_sort(arr, len);
    //show_quick_sort(arr, len);
    //show_my_quick_sort(arr, len);
    show_bheap_sort(arr, len);
    show_my_bheap_sort(arr, len);
    //show_oop_quick_sort(arr, len);
    //show_selection_sort(arr, len);

    free(arr);
}

