#include <stdio.h>
#include <stdlib.h>

/*
 * implement align_malloc and align_free
 */

typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned char u8;

/**
 * allow caller to specify a alignment number
 * will actually allocate a larger space and store the ori pointer addr
 * in front 8-bytes of the return pointer
 */
void *
align_malloc(size_t size, u8 alignment)
{
    u32 offset = alignment - 1 + sizeof(void*);
    void *ori = malloc(size + offset);
    if (!ori) return NULL;
    void **ret = (void**) (((u64)ori + offset) & (~(alignment - 1)));
    ret[-1] = ori;
    printf("alloc ori is %p\n", ori);
    return ret;
}

/**
 * get the ori pointer and free
 */
void
align_free(void *ptr)
{
    void *ori = ((void**)ptr)[-1];
    printf("free ori is %p\n", ori);
    free(ori);
}

int main()
{
    void *p1, *p2;
    p1 = malloc(10);
    p2 = align_malloc(10, 8);
    printf("%p\n", p1);
    printf("%p\n", p2);
    free(p1);
    align_free(p2);
}
