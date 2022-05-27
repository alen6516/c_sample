#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include "../util/util.h"

/* Node */
struct __node {
    u64 size:  32,
        spare: 32;
    u64 hash;
    struct __node *next;
    char str[0];
//} __attribute__((packed));
};
typedef struct __node Node;

// static inline
u64 node_get_hash(Node *node);
u64 node_get_hash_from_str(char *str);

// API
Node *node_create(char *str);
Node *node_copy(Node *node);
void node_show(Node *node);
void node_show_list(Node *node);

/* HashTable */
typedef struct __hash_table {
    u32 size;
    Node *array[0];
} HashTable;

//static inline u8
static u8   table_get_idx(HashTable *table, u64 code);

// API
HashTable*  table_create(u32 size);
Node* table_insert(HashTable *table, Node *node);
Node* table_search(HashTable *table, Node *node);
Node* table_remove(HashTable *table, Node *node);
void  table_dump(HashTable *table);

#endif
