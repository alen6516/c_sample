#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/util.h"
#include "hash_table.h"

// calculate the hash of the input string
u64
node_get_hash(Node *node)
{
    u64 ret = 0;
    u32 len = strlen(node->str);
    u64 inc;
    for (u32 i=0; i<len; i++) {
        //ret += ( (*(s+i))<<(len-1-i) );
        inc = ( *(node->str+i) << i);
        ret += inc;
    }

    DEBUG("hash = %lu\n", ret);
    return ret;
}

u64
node_get_hash_from_str(char *str)
{
    u64 ret = 0;
    u32 len = strlen(str);
    u64 inc;
    for (u32 i=0; i<len; i++) {
        //ret += ( (*(s+i))<<(len-1-i) );
        inc = ( *(str+i) << i);
        ret += inc;
    }

    DEBUG("hash = %lu\n", ret);
    return ret;
}

// allocate node, populate string and hash
Node*
node_create(char *str)
{
    Node *ret;
    u32 len = strlen(str);
    u32 size = sizeof(Node) + len + 1;
    ret = (Node *) malloc(size);
    if (ret) {
        ret->size = size;
        strncpy(ret->str, str, len+1);
        ret->hash = node_get_hash_from_str(str);
    }
    return ret;
}

Node*
node_copy(Node *node)
{
    Node *ret;
    ret = (Node *) malloc(node->size);
    if (ret) {
        memcpy(ret, node, node->size);
    }
    return ret;
}

void
node_show(Node *node)
{
    printf("node = %p\n", node);
    printf("node->size = %d\n", node->size);
    printf("node->str  = %s\n", node->str);
    printf("node->hash = %lu\n", node->hash);
    printf("node->next = %p\n", node->next);
}

void
node_show_list(Node *node)
{
    u32 count = 0;
    while (node) {
        printf("%s => ", node->str);
        count ++;
        node = node->next;
    }
    printf("NULL\n");
    printf("total %d nodes\n", count);
}

HashTable*
table_create(u32 size)
{
    HashTable *table;
    u32 total_size = sizeof(HashTable) + sizeof(TableBucket) * size;
    table = (HashTable *) malloc(total_size);
    if (table) {
        memset(table, 0, total_size);
        table->size = size;
        for (int i=0; i < size; i++) {
            table->array[i].lock = PTHREAD_MUTEX_INITIALIZER;
        }
    }
    return table;
}

// calculate index from the input hash
static u8
table_get_idx(HashTable *table, u64 hash)
{
    return hash % table->size;
}

// node insert to table
Node*
table_insert(HashTable *table, Node *node)
{
    u8 key = table_get_idx(table, node->hash);
    TableBucket *bucket = table->array[key];

    pthread_mutex_lock(&bucket->lock);

    Node *head = bucket->head;
    node->next = head;
    bucket->head = node;

    pthread_mutex_unlock(&bucket->lock);

    DEBUG("%s\n", node->str);
    DEBUG("node = %p\n", node);
    DEBUG("table[%d] = %p\n", key, table[key]);
    
    return node;
}

// populate a node and search if the string in the table
Node*
table_search(HashTable *table, Node *node)
{
    u64 hash = node_get_hash(node);
    u8 key = table_get_idx(table, hash);
    TableBucket *bucket = table->array[key];

    Node *curr = bucket->head;

    while (curr) {
        if (hash == curr->hash && 
               0 == strcmp(node->str, curr->str)) {

            return curr;
        } else {
            curr = curr->next;
        }
    }

    return NULL;
}

// populate a node and remove if the string in the table
Node*
table_remove(HashTable *table, Node *node)
{
    u64 hash = node_get_hash(node);
    u8 key = table_get_idx(table, hash);
    TableBucket *bucket = table->array[key];
    Node *curr;
    Node **next;

    pthread_mutex_lock(&bucket->lock);

    curr = bucket->head;

    if (!curr) {
        pthread_mutex_unlock(&bucket->lock);
        return NULL;
    }

    next = &bucket->head;

    while (curr) {
        if (hash == curr->hash && 
               0 == strcmp(node->str, curr->str)) {

            break;
        } else {
            next = &curr->next;
            curr = curr->next;
        }
    }

    if (curr) {
        *next = curr->next;
    }

    pthread_mutex_unlock(&bucket->lock);
    return curr;
}

void
table_dump(HashTable *table)
{
    Node *curr;
    int count;
    printf("--- table dump ---\n");
    printf("table array size = %d\n", table->size);
    for (int i=0; i < table->size; i++) {
        printf("idx %2d:  ", i);
        count = 0;
        curr = table->array[i];
        while (1) {
            //printf("%p", curr);
            if (!curr) {
                break;
            } else {
                printf("%s", curr->str);
                printf(" ==> ");
                count ++;
                curr = curr->next;
            }
        }
        printf(" [ %d nodes ]\n", count);
        //printf("\n");
    }
}
