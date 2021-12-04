#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "list.h"

list_t* list;

int main () {
    node_t root;
    root.val = 0;
    root.next = NULL;

    list = init_list((void*)&root, get_ref_of_next);

    printf("val of root->next: %p\n", ((node_t*)(list->root))->next);
    printf("addr of root->next: %p\n", &((node_t*)(list->root))->next);

    printf("val of root->next: %p\n", root.next);
    printf("---- adding n1 ----\n");

    node_t n1;
    n1.val = 1;
    n1.next = NULL;

    list_put(list, (void*)&n1, (void**)&n1.next);
    printf("val of root->next: %p\n", root.next);
    printf("addr of n1: %p\n", &n1);


    printf("---- adding n2 ----\n");
    node_t n2;
    n2.val = 2;
    n2.next = NULL;

    list_put(list, (void*)&n2, (void**)&n2.next);
    printf("val of root->next: %p\n", root.next);
    printf("addr of root->next: %p\n", &root.next);
    printf("val of n1->next: %p\n", n1.next);
    printf("addr of n2: %p\n", &n2);


    void *out;
    printf("---- taking n1 ----\n");
    out = list_take(list, get_next);
    printf("val of out: %p\n", out);
    printf("val of root->next: %p\n", root.next);
    printf("val of list->root->next: %p\n", ((node_t*)(list->root))->next);
}

