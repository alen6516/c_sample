#include <stdio.h>
#include <stdlib.h>
#include "list.h"

node_t *head;
pthread_mutex_t node_lock;

node_t **node_init()
{
    node_lock = PTHREAD_MUTEX_INITIALIZER;
    head = NULL;
    return &head;
}

// push to head, return new head if success
node_t * node_push(int val)
{
    if (!head) return NULL;

    node_t *node;

    node = (node_t *)malloc(sizeof(node_t));
    if (!node) {
        printf("malloc fail\n");
        return NULL;
    }

    node->val = val;


    pthread_mutex_lock(&node_lock);
    node->next = head;
    head = node;
    pthread_mutex_unlock(&node_lock);

    return head;
}

// pop from tail, return popped node if success
node_t *node_pop()
{
    pthread_mutex_lock(&node_lock);

    node_t *priv = NULL;
    node_t *curr = head;

    if (!curr)  // no job
        goto done;

    while (curr->next) {
        priv = curr;
        curr = curr->next;
    }

    if (priv) priv->next = NULL;    // several jobs
    else head = NULL;               // only 1 job

done:
    pthread_mutex_unlock(&node_lock);
    return curr;
}

#ifdef alan
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
#endif
