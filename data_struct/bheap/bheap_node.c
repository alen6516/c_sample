/*
 * Binary heap sorting is a sorting method.
 * It use array to store a binary tree, and always keeps the top node as the Max/Min node.
 * 
 * When adding new node, the new node will be appened to the tail,
 * and call bheap_bottomup() to bubble it up to the right place.
 *
 * When taking out the top node, it will call bheap_topdown() to resort
 * the bheap again.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../utils/arr.h"
#include "../../utils/utils.h"


#define MAX_SIZE 20
#define IS_ODD(val) ((val) & 0x1)

typedef struct __node {
    int val;
} Node;

struct __bheap {
    int arr_size;
    int len;
    Node *arr[0];
} __attribute__((packed));
typedef struct __bheap Bheap;

Bheap *bheap_create(int size)
{
    if (size <= 0)
        size = MAX_SIZE;

    Bheap *bheap = (Bheap*) malloc(sizeof(Bheap)+sizeof(Node*)*size);
    if (!bheap)
        goto fail;

    bheap->arr_size = size;
    bheap->len = 0;
    printf("Create bheap of size %d\n", bheap->arr_size);

    return bheap;

fail:
    return NULL;
}

void bheap_show(Bheap *bheap)
{
    int depth = 0;
    int _len = bheap->len;

    // calculate depth
    while (_len) {
        depth ++;
        _len = _len >> 1;
    }

    printf("bheap len   = %d\n", bheap->len);
    printf("bheap depth = %d\n", depth);

    for (int i=0; i<depth; i++) {
        for (int j=0; j<(1<<i); j++) {
            if ((1<<i)+j-1 < bheap->len) {
                printf("%d, ", bheap->arr[(1<<i)+j-1]->val);
            } else {
                break;
            }
        }
        printf("\n");
    }
}

/**
 * Bubble the tail up to the right place by continuing to swap with the parent
 * if it is larger
 */
static void bheap_bottomup(Bheap *bheap)
{
    if (!bheap || bheap->len < 2) return;

    int curr_idx = bheap->len-1;
    int parent_idx;
    do {
        if (IS_ODD(curr_idx)) {
            parent_idx = (curr_idx-1) >> 1;
        } else {
            parent_idx = (curr_idx-2) >> 1;
        }

        // compare with parent and swap
        if (bheap->arr[parent_idx]->val < bheap->arr[curr_idx]->val) {
            SWAP(bheap->arr[parent_idx], bheap->arr[curr_idx]);
        }

        curr_idx = parent_idx;
    } while (curr_idx != 0);
}

// create a double-sized bheap and copy data to it
Bheap* bheap_extend(Bheap *bheap)
{
    Bheap *new;
    int old_size = bheap->arr_size;
    int new_size = old_size*2;

    new = (Bheap*) malloc(sizeof(Bheap)+sizeof(Node*)*new_size);
    if (!new)
        return bheap;

    memcpy(new, bheap, sizeof(Bheap)+sizeof(Node*)*old_size);
    new->arr_size = new_size;
    free(bheap);
    return new;
}

/**
 * API
 * Append the new value and bubble it up
 */
int bheap_add(Bheap **_bheap, Node *node)
{
    Bheap *new;
    Bheap *bheap = *_bheap;

    if (bheap->len == bheap->arr_size) {
        new = bheap_extend(bheap);
        if (new == bheap) {
            printf("bheap is full and fails to extend\n");
            return -1;
        } else {
            *_bheap = bheap = new;
            printf("bheap is full and succeeds to extend, new size is %d\n", bheap->arr_size);
        }
    }

    bheap->arr[bheap->len++] = node;
    bheap_bottomup(bheap);

    printf("bheap add node %d, len become %d\n", node->val, bheap->len);

    return 0;
}

/**
 * Compare parent with children and exchange if one of the children is larger
 */
static void bheap_topdown(Bheap *bheap)
{
    if (!bheap || !bheap->len) return;

    int curr_idx = 0;
    int lchild_idx, rchild_idx;
    lchild_idx = (curr_idx << 1) + 1;
    rchild_idx = (curr_idx << 1) + 2;

    while (lchild_idx < bheap->len || rchild_idx < bheap->len) {
        if (rchild_idx < bheap->len && bheap->arr[rchild_idx]->val > bheap->arr[lchild_idx]->val) {
            // rchild is max
            SWAP(bheap->arr[curr_idx], bheap->arr[rchild_idx]);
            curr_idx = rchild_idx;
            lchild_idx = (curr_idx << 1) + 1;
            rchild_idx = (curr_idx << 1) + 2;

        } else if (bheap->arr[lchild_idx]->val > bheap->arr[curr_idx]->val) {
            // lchild is max
            SWAP(bheap->arr[curr_idx], bheap->arr[lchild_idx]);
            curr_idx = lchild_idx;
            lchild_idx = (curr_idx << 1) + 1;
            rchild_idx = (curr_idx << 1) + 2;

        } else {
            // curr is not smaller than children
            break;
        }
    }
}

/**
 * API
 * Return the top and move the tail to the top and do bheap topdown
 */
Node* bheap_pop(Bheap *bheap)
{
    if (!bheap || !bheap->len) return NULL;

    Node *ret = bheap->arr[0];
    bheap->arr[0] = bheap->arr[bheap->len-1];
    bheap->len --;

    bheap_topdown(bheap);
    return ret;
}

// argv is the length of array
int main(int argc, char *argv[])
{
    srand(time(NULL));

    int len = MAX_SIZE;
    if (argc == 2) {
        len = strtol(argv[1], NULL, 10);
        if (len > MAX_SIZE) {
            len = MAX_SIZE;
        }
    }
    printf("len = %d\n", len);

    /* arr to show the number before/after sorting */
    int *arr_pre = (int*) malloc(sizeof(int)*len);
    int *arr_post = (int*) malloc(sizeof(int)*len);

    Bheap *bheap = bheap_create(len/2);
    if (!bheap) {
        printf("fail to allocate bheap\n");
        return -1;
    }

    // generate arr_pre
    for (int i=0; i<len; i++) {
        arr_pre[i] = (rand() % 100 + 1);
    }
    arr_show(arr_pre, len);

    /* store data to bheap */
    Node *node;
    for (int i=0; i<len; i++) {
        node = (Node*) malloc(sizeof(Node));
        node->val = arr_pre[i];
        bheap_add(&bheap, node);
    }
    bheap_show(bheap);

    /* pop the bheap and store to arr_post */
    for (int i=0; bheap->len; i++) {
        printf("=================\n");
        node = bheap_pop(bheap);
        arr_post[i] = node->val;
        free(node);
        printf("pop: %d\n", arr_post[i]);
        bheap_show(bheap);
    }

    /* show array */
    arr_show(arr_pre, len);
    arr_show(arr_post, len);
}
