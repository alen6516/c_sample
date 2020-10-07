/***
 File Name: a.c
 Author: alen6516
 Created Time: 2018-10-28
***/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node Node;

Node *createNode(int);
void show(Node *);
void reverseShow(Node *);
int len(Node *);
int pop(Node *);

/* add node */
Node* addHead(Node *, int);
void addNext(Node *, int);
void addTail(Node *, int);

/* delete node */
Node* delHead(Node *);
void delNext(Node *);
void delTail(Node *);

void reverse(Node **, Node *, Node *);
Node* reverse2(Node *);

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    show(head);
    printf("len is %d\n", len(head));
    reverseShow(head);

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
    
    head = reverse2(head);
    show(head);
    printf("\n");
    
    printf("pop out %d\n", pop(head));
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

void reverseShow(Node *node) {
    if(node->next) {
        reverseShow(node->next);
        printf("%d\n", node->data);
    } else {
        printf("%d\n", node->data);
    }
}

int len(Node *node) {
    int i = 0;
    for(; node; i++, node=node->next);
    return i;
}

int pop(Node *curr) {
    assert(curr);

    int rt = 0;
    if(!curr->next) {
        rt = curr->data;
        free(curr);
        return rt;
    }

    Node *currNext = curr->next;
    while(currNext->next) {
        curr = currNext;
        currNext = curr->next;
    }
    rt = currNext->data;
    free(currNext);
    curr->next = NULL;
    return rt;
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

void reverse(Node **head, Node *curr, Node *currNext) {
    if(!currNext) {
        return;
    }
    if(currNext->next) {
        reverse(head, currNext, currNext->next);
    } else {
        *head = currNext;
    }
    currNext->next = curr;
    curr->next = NULL;
}

Node* reverse2(Node *node) {
    if(node->next) {
        Node* newHead = reverse2(node->next);
        node->next->next = node;
        node->next = NULL;
        return newHead;
    } else {
        return node;
    }
}
