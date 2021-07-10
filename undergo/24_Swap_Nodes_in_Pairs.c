/*
Runtime: 0 ms, faster than 100.00% of C online submissions for Swap Nodes in Pairs.
Memory Usage: 5.8 MB, less than 91.22% of C online submissions for Swap Nodes in Pairs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head){

    if (!head || !head->next) return head;

	struct ListNode *ret, *curr, *next;
    curr = head;
    ret = head->next;
    struct ListNode **tmp = NULL;

    while (curr && (next = curr->next)) {
        if (tmp) {
            *tmp = next;
        }

        curr->next = next->next;
        next->next = curr;

        tmp = &(curr->next);

        curr = curr->next;
    }
    return ret;
}


int main () {

    srand(time(NULL));

    // making list
    struct ListNode *head, *curr, *prev;
    prev = NULL;
	
    int num = (rand() % 10)+ 2;

    for (int i=0; i<num; i++) {
        curr = (struct ListNode*) malloc(sizeof(struct ListNode));
        curr->val = rand() % 50;
        if (prev) {
            prev->next = curr;
        } else {
            head = curr;
        }
        prev = curr;
    }

    // show list
    printf("num = %d\n", num);
    for (struct ListNode *p = head; p; p = p->next) {
        printf("%d -> ", p->val);
    }
    printf("\n");

    head = swapPairs(head);

    for (struct ListNode *p = head; p; p = p->next) {
        printf("%d -> ", p->val);
    }
    printf("\n");
}
