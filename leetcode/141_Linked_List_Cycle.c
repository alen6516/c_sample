#include <stdio.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// Runtime 6 ms Beats 95.41%
// Memory 11.22 MB Beats 38.25%
// less if-statement makes it faster
bool hasCycle(struct ListNode *head) {
    if (!head || !head->next) return false;

    struct ListNode *slow, *fast;
    slow = head;
    fast = head->next;

    while (fast && fast != slow) {
        slow = slow->next;
        if (fast->next)
            fast = fast->next->next;
        else return false;
    }

    return !!fast;
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
