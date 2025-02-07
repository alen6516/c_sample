#include <stdio.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// Runtime 10 ms Beats 63.07%
// Memory 11.52 MB Beats 9.15%
bool hasCycle(struct ListNode *head) {
    if (!head) return false;

    struct ListNode *slow, *fast;
    slow = head;
    fast = head->next;

    while (fast != NULL) {
        if (slow == fast) return true;

        slow = slow->next;

        fast = fast->next;
        if (!fast) return false;
        else if (fast == slow) return true;

        fast = fast->next;
        if (!fast) return false;
        else if (fast == slow) return true;
    }

    return false;
}

int main() {
    // Example usage
    struct ListNode node1 = {1, NULL};
    struct ListNode node2 = {2, NULL};
    struct ListNode node3 = {3, NULL};
    struct ListNode node4 = {4, NULL};

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node2; // Creates a cycle

    if (hasCycle(&node1)) {
        printf("Cycle detected.\n");
    } else {
        printf("No cycle.\n");
    }

    return 0;
}
