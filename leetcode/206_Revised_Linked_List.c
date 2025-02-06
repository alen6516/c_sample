#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};


// my solution {
struct ListNode* getNext(struct ListNode *node)
{
    struct ListNode *root, *next;
    next = node->next;
    if (!next) return node;
    root = getNext(next);
    next->next = node;

    return root;
}

struct ListNode* reverseList(struct ListNode* head) {
    if (!head) return NULL;
    struct ListNode *root;
    root = getNext(head);
    head->next = NULL;
    return root;
}
// } my solution

struct ListNode* reverseList(struct ListNode* head) {
    if (!head || !head->next) return head;

    struct ListNode *prev, *curr, *next;
    prev = head;
    curr = head->next;
    next = curr->next;
    while (1) {
        curr->next = prev;
        prev = curr;
        if (next) {
            curr = next;
            next = curr->next;
        } else
            return curr;
    }
}

// below is for testing

// Function to create a new node
struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    // Creating the linked list: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
    struct ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Original list: ");
    printList(head);

    // Reversing the list
    head = reverseList(head);

    printf("Reversed list: ");
    printList(head);

    return 0;
}
