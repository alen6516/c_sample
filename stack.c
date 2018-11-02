/***
 File Name: stack.c
 Author: alen6516
 Created Time: 2018-11-02
***/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node Node;

void show();

Node* push(Node *, int);
int pop(Node *);

int main(void) {
    Node *top = malloc(sizeof(Node));
    top->data = 1;
    top->next = NULL;

    show(top);
    printf("\n");

}

void show(Node *node) {
    int i = 1;
    while(node) {
        printf("%d is %d\n", i++, node->data);
        node = node->next;
    }
}

Node* push(Node *top, int val) {
    Node *p = malloc(sizeof(Node));
    p->data = val;
    p->next = top;
    return p;
}
