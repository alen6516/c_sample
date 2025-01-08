#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arr.h"

/* sort object { */
struct __sort_class;
struct __sort;

#define SORT_CLASS_METHOD(type) \
    void (*sort_it)(type*)

typedef struct __sort_class {
    SORT_CLASS_METHOD(struct __sort);
    // no data member
} SortClass;

typedef struct __sort {
    SortClass *sort_class;
    int *arr;
    int arr_len;
} Sort;

void sort_it(Sort* sort) {
    return;
}

// define a sort class
SortClass sort_class = {
    .sort_it = sort_it
};
/* } sort object */

/* quick sort object { */
struct __quick_sort_class;
struct __quick_sort;

#define QUICK_SORT_CLASS_METHOD(type) \
    void (*sort_it)(type*, int, int); \
    void (*sort_show)(type*)

typedef struct __quick_sort_class {
    QUICK_SORT_CLASS_METHOD(struct __quick_sort);
} QuickSortClass;

typedef struct __quick_sort {
    QuickSortClass *quick_sort_class;
    int *arr;
    int arr_len;
} QuickSort;

void quick_sort_it (QuickSort *, int, int);
void quick_sort_show(QuickSort *);

//define a quick sort class
QuickSortClass q_sort_class = {
    .sort_it = quick_sort_it,
    .sort_show = quick_sort_show
};
/* } quick sort obj */


/* util { */
#define ARR_SIZE(arr) (int)sizeof(arr)/sizeof(arr[0])

#define SWAP(a, b) do {     \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while (0)

void quick_sort_show(QuickSort *q_sort)
{
    for (int i = 0; i < q_sort->arr_len; i++) {
        printf("%d, ", q_sort->arr[i]);
    }
    printf("\n");
}
/* } util */


/* quick sort method { */
int __quick_sort_partition (QuickSort *q_sort, int left, int right)
{
    printf("in this partition, left = %d, right = %d\n", left, right);

    int mid_idx = right;
    right--;
    int swap_with_mid_before_return = -1;

    for (;left < right; left++) {
        if (q_sort->arr[left] > q_sort->arr[mid_idx]) {     // if this one is larger then mid

            swap_with_mid_before_return = left;

            // find a small one from right
            for (; right > left ; right--) {
                if (q_sort->arr[right] < q_sort->arr[mid_idx]) {

                    // if find, then swap them
                    SWAP(q_sort->arr[left], q_sort->arr[right]);
                    q_sort->quick_sort_class->sort_show(q_sort);
                    swap_with_mid_before_return = right;
                    break;
                }
            }
        } 
    }

    if (swap_with_mid_before_return != -1) {
        SWAP(q_sort->arr[swap_with_mid_before_return], q_sort->arr[mid_idx]);
        printf("swap before return\n");
        q_sort->quick_sort_class->sort_show(q_sort);
        return swap_with_mid_before_return;
    } else {
        return right;
    }
}

void quick_sort_it(QuickSort *q_sort, int left, int right)
{
    if (right == left+1) {
        if (q_sort->arr[left] > q_sort->arr[right]) {
            SWAP(q_sort->arr[left], q_sort->arr[right]);
        }
        return;
    }

    int q;

    q = __quick_sort_partition(q_sort, left, right);
    printf("partition return %d\n", q);
    

    if (q != left)
        quick_sort_it(q_sort, left, q);
    if (q != right)
        quick_sort_it(q_sort, q, right);
}
/* } quicl sort method */

int main () {
    int arr[] = {1, 3, -1, 2, -4, 9, 0, 1, -5};
    QuickSort q_sort;
    q_sort.quick_sort_class = &q_sort_class;
    q_sort.arr = arr;
    q_sort.arr_len = ARR_SIZE(arr);

    q_sort.quick_sort_class->sort_it(&q_sort, 0, q_sort.arr_len-1);
    q_sort.quick_sort_class->sort_show(&q_sort);
}
