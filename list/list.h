#ifndef LIST_H
#define LIST_H

/* head is dummy node, no data */

typedef struct Node {
    int val;
    struct Node *next;
} node_t;


node_t * node_append(node_t *, node_t *);
node_t * node_remove(node_t *, int);


node_t * node_push(node_t *, node_t *);
node_t * node_pop(node_t *);
#endif
