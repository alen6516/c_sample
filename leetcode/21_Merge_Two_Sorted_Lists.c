/*
Runtime: 4 ms, faster than 82.71% of C online submissions for Merge Two Sorted Lists.
Memory Usage: 6.1 MB, less than 73.40% of C online submissions for Merge Two Sorted Lists.
*/

#include <stdio.h>
#include <stdlib.h>
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

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){

	// filter extreme cases
	if (!l1) {
		return l2;
	} else if (!l2) {
		return l1;
	}

	struct ListNode *curr;		// curr node
	struct ListNode *standby;	// the node that will be compared with curr->next
	struct ListNode *tmp;
	struct ListNode *ret;

		
	if (l1->val > l2->val) {
		ret = curr = l2;
		standby = l1;
	} else {
		ret = curr = l1;
		standby = l2; 
	}

	while (curr->next) {
		if (curr->next->val <= standby->val) {
			curr = curr->next;

		} else {
			// swap curr and standby
			tmp = curr->next;
			curr->next = standby;
			standby = tmp;

			curr = curr->next;
		}
	}

	curr->next = standby;
	return ret;
}


unsigned int getRandNum() {
    FILE *fp;
    if ((fp = fopen("/dev/urandom", "r")) == NULL) {
        fprintf(stderr, "Error!, Could not open /dev/urandom to read.\n");
        exit(-1);
    }

    int result = fgetc(fp);
	return result;
}

int main() {
	int len1 = (getRandNum() % 7 )+1;
	int len2 = (getRandNum() % 7 )+1;

	struct ListNode *l1, *l2, *curr, *prev;

	l1 = l2 = curr = prev = NULL;

	// generate list 1
	for (int i=0; i<len1; i++) {
		curr= (struct ListNode*)malloc(sizeof(struct ListNode));
		curr->val = getRandNum() % 50;
		curr->next = NULL;
		if (!l1) l1 = curr;
		if (!prev) {
			prev = curr;
			printf("%d", curr->val);
		} else {
			curr->val += prev->val;
			prev->next = curr;
			prev = curr;
			printf("->%d", curr->val);
		}
	}
	printf("\n");

	prev = NULL;

	// generate list 2
	for (int i=0; i<len2; i++) {
		curr= (struct ListNode*)malloc(sizeof(struct ListNode));
		curr->val = getRandNum() % 50;
		curr->next = NULL;
		if (!l2) l2 = curr;
		if (!prev) {
			prev = curr;
			printf("%d", curr->val);
		} else {
			curr->val += prev->val;
			prev->next = curr;
			prev = curr;
			printf("->%d", curr->val);
		}
	}
	printf("\n");
	
	struct ListNode *ret = mergeTwoLists(l1, l2);
	while(ret) {
		printf("%d->", ret->val);
		ret = ret->next;
	}
	printf("\n");
}
