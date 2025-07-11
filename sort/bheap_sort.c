#include <stdio.h>

struct __bheap {
    int size;
    int len;
    int arr[0];
} __attribute__((packed));
typedef struct __bheap Bheap;


Bheap *bheap_create();
static Bheap* bheap_expand();
static void bheap_topdown();
static void bheap_bottomup();
void bheap_sort

#define SIZE 10

Bheap *bheap_create()
{
    Bheap *ret;
    ret = (Bheap *)malloc(sizeof(Bheap)+);
}
