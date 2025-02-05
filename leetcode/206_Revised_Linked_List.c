/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

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
    return getNext(head);
}

