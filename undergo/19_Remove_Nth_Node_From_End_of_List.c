/*
Runtime: 4 ms, faster than 52.75% of C online submissions for Remove Nth Node From End of List.
Memory Usage: 5.7 MB, less than 81.45% of C online submissions for Remove Nth Node From End of List.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {

    // first handle spacial case
    if (n == 1 && !head->next) {
        return NULL;
    }

    // prepare variable
    struct ListNode* curr = head;
    struct ListNode* pp = NULL;     // the prev node of the target node to remove

    // main logic
    while (curr) {
        if (pp) {
            pp = pp->next;
        }

        if (n == 0 && !pp) {
            pp = head;
        }
        if (n > 0) {
            n--;
        }
        curr = curr->next;
    }

    if (pp) {
        pp->next = pp->next->next;
        return head;
    } else {
        if (n==0) {
            // n equal to the total num of list => remove the 1st node
            return head->next;
        } else {
            // wrong n, n should < total num of the list
            return NULL;
        }
    }
}

#define NUM 2

void show(struct ListNode* head) {
    while(head) {
        printf("%d, ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main () {
    struct ListNode* p = NULL;
    struct ListNode* prev = NULL;
    struct ListNode* head = NULL;

    for (int i=0; i<NUM; i++) {
        p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = i;
        p->next = NULL;

        if (!prev) {
            head = prev = p;

        } else {
            prev->next = p;
            prev = p;
        }
    }

    show(head);

    head = removeNthFromEnd(head, 2);
    show(head);
}
