/***
 File Name: a.c
 Author: alen6516
 Created Time: 2018-10-28
***/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node Node;

Node *createNode(int);
void show(Node *);
void showReverse(Node *);
int len(Node *);

/* add node */
Node* addHead(Node *, int);
void addNext(Node *, int);
void addTail(Node *, int);

/* delete node */
Node* delHead(Node *);
void delNext(Node *);
void delTail(Node *);

void reverse(Node **, Node *, Node *);

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    show(head);
    printf("len is %d\n", len(head));
    showReverse(head);

    head = addHead(head, 4);
    show(head);
    printf("\n");
    
    addNext(head, 5);
    show(head);
    printf("\n");
    
    addTail(head, 6);
    show(head);
    printf("\n");

    head = delHead(head);
    show(head);
    printf("\n");
    
    delNext(head);
    show(head);
    printf("\n");
    
    delTail(head);
    show(head);
    printf("\n");
    
    reverse(&head, head, head->next);
    show(head);
    printf("\n");
}

Node *createNode(int val) {
    Node *p = malloc(sizeof(Node));
    if(!p) {
        printf("memory not enough\n");
        exit(1);
    }
    p->data = val;
    return p;
}

void show(Node *head) {
    Node *tmp = head;
    for(int i=1; tmp; i++, tmp=tmp->next) {
        printf("%d Node is %d\n", i, tmp->data);
    }
}

void showReverse(Node *tmp) {
    if(tmp->next) {
        showReverse(tmp->next);
        printf("%d\n", tmp->data);
    } else {
        printf("%d\n", tmp->data);
    }
}

int len(Node *node) {
    int i = 0;
    for(; node; i++, node=node->next);
    return i;
}

int indexOf(Node *node, int val) {
    for(int i=0; node; i++) {
        if(node->data = val) return i;
    }
    return -1;
}

Node* addHead(Node *head, int val) {
    Node *newNode = createNode(val);
    newNode->next = head;
    return newNode;
}

void addNext(Node *node, int val) {
    Node *newNode = createNode(val);
    newNode->next = node->next;
    node->next = newNode;
}

void addTail(Node *node, int val) {
    while(node->next) {
        node = node->next;
    }
    Node *newNode = createNode(val);
    node->next = newNode;

}

Node* delHead(Node *head) {
    Node *tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

void delNext(Node *node) {
    Node *tmp = node->next;
    node->next = tmp->next;
    free(tmp);
}

void delTail(Node *node) {
    Node *tmp = node;
    while(tmp->next) {
        node = tmp;
        tmp = tmp->next;
    }
    node->next = NULL;
    free(tmp);
}

void reverse(Node **head, Node *curr, Node *next_) {
    if(!next_) {
        return;
    }
    if(next_->next) {
        reverse(head, next_, next_->next);
    } else {
        *head = next_;
    }
    next_->next = curr;
    curr->next = NULL;
}
