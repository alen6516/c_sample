#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* return node if success, NULL if fail */
node_t * node_append(node_t *head, int val)
{
    if (!head) return NULL;

    node_t *node, **iter;

    node = (node_t *)malloc(sizeof(node_t));
    if (!node) {
        printf("malloc fail\n");
        return NULL;
    }
    node->val = val;

    iter = &head->next;
    while (*iter) iter = &(*iter)->next;
    *iter = node;

    return node;
}

/* return head if success, NULL if fail */
node_t * node_remove(node_t *head, int input)
{
    if (!head) return NULL;

    node_t *iter = head;
    node_t *ret = NULL;
    while (iter->next) {
        if (iter->next->val == input) {
            ret = iter->next;
            iter->next = iter->next->next;
            break;
        } else
            iter = iter->next;
    }

    if (ret) {
        free(ret);
        ret = head;
    }

    return ret;
}

/* return node if success, NULL if fail */
node_t * node_push(node_t *head, int val)
{
    if (!head) return NULL;

    node_t *node;

    node = (node_t *)malloc(sizeof(node_t));
    if (!node) {
        printf("malloc fail\n");
        return NULL;
    }

    node->val = val;
    node->next = head;

    return node;
}

/* return head if success, NULL if fail */
node_t *node_pop(node_t *head)
{
    if (!head) return NULL;

    node_t *priv = NULL;
    node_t *curr = head;

    while (curr->next) {
        priv = curr;
        curr = curr->next;
    }

    if (priv) priv->next = NULL;
    return curr;
}
