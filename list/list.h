#ifndef LIST_H
#define LIST_H

#include <pthread.h>

/* head is dummy node, no data */

typedef struct Node {
    int val;
    struct Node *next;
} node_t;

// head of the list, and it is a valid node
extern node_t *head;
extern pthread_mutex_t node_lock;

node_t * node_push(int);
node_t * node_pop();

#ifdef alan
node_t * node_append(node_t *, node_t *);
node_t * node_remove(node_t *, int);
#endif

#endif
