#include <stdio.h>

struct __bheap {
    int size;
    int len;
    int arr[0];
} __attribute__((packed));
typedef struct __bheap Bheap;


Bheap *bheap_create(int);
static Bheap* bheap_expand(Bheap*);
static void bheap_topdown();
static void bheap_bottomup();
void bheap_sort
void bheap_push();
void bheap_pop();

#define SIZE 10

Bheap *bheap_create(int size)
{
    Bheap *ret;
    if (size == 0) size = SIZE;
    ret = (Bheap *)malloc(sizeof(Bheap)+size*sizeof(int));
    ret->size = size;
    ret->len = 0;
    return ret;
}

void bheap_push(Bheap *bheap, int val)
{
    if (bheap->size == bheap->len) {
        // full
        bheap = bheap_expand(Bheap *bheap);
    }

    bheap->arr[bheap->len-1] = val;
    bheap->len ++;
    bheap_bottomup(bheap);
}

int bheap_pop(Bheap *bheap)
{
    if (bheap->len == 0) return -1;

    int ret = bheap->arr[0];
    bheap->arr[0] = bheap->arr[bheap->len-1];
    bheap->len --;
    bheap_topdown(bheap);
    return ret;
}

static Bheap *bheap_expand(Bheap *bheap)
{
    int size = bheap->size * 2;
    Bheap *ret = (Bheap *)malloc(sizeof(Bheap)+size*sizeof(int));
    ret->size = size;
    ret->len = bheap->len;
    memcpy(ret->arr, bheap->arr, sizeof(int)*bheap->len);
    free(bheap);
    return ret;
}
