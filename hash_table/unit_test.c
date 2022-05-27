#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../util/util.h"
#include "hash_table.h"

#define RESULT_SIZE    100
char expect_result[RESULT_SIZE];
char actual_result[RESULT_SIZE];

#define SHOW_TEST() ({                  \
    printf("=== %s ===\n", __func__);   \
})

#define SHOW_FAIL() ({                          \
    printf("*** fail in %s ***\n", __func__);   \
})

Node*
test_node_create(char *str)
{
    SHOW_TEST();

    Node *ret;
    ret = node_create(str);
    if (ret) {
        node_show(ret);
    } else {
        SHOW_FAIL();
    } 

    return ret;
}

Node*
test_node_copy(Node *node)
{
    SHOW_TEST();

    Node *ret;
    ret = node_copy(node);
    if (ret) {
        node_show(node);
        node_show(ret);
    } else {
        SHOW_FAIL();
    }

    return ret;
}

void
test_node_get_hash(Node *node, Node *copy, Node *node2)
{
    SHOW_TEST();

    u64 hash = node_get_hash(node);

    if (hash == node_get_hash(copy) &&
        hash != node_get_hash(node2)) {

        printf("node->hash = %lu\n", hash);
        printf("copy->hash = %lu\n", copy->hash);
        printf("node2->hash = %lu\n", node2->hash);
    } else {
        SHOW_FAIL();
    }
}

void
test_node_get_hash_from_str(Node *node, Node *copy, Node *node2)
{
    SHOW_TEST();

    u64 hash = node_get_hash(node);
    
    if (hash == node_get_hash_from_str(copy->str) &&
        hash != node_get_hash_from_str(node2->str)) {

        printf("node->hash = %lu\n", hash);
        printf("copy->hash = %lu\n", copy->hash);
        printf("node2->hash = %lu\n", node2->hash);
    } else {
        SHOW_FAIL();
    }
}

HashTable*
test_table_create(u32 size)
{
    SHOW_TEST();

    HashTable *ret;
    ret = table_create(size);

    if (ret) {
        table_dump(ret);
    } else {
        SHOW_FAIL();
    }

    return ret;
}

void
test_table_insert(HashTable *table, Node *node)
{
    SHOW_TEST();

    table_insert(table, node);
    table_dump(table);
}

void
test_table_search(HashTable *table, Node *node, Node *node2)
{
    SHOW_TEST();

    if (table_search(table, node) &&
        !table_search(table, node2)) {

        printf("node (%s, %lu) is in table\n", node->str, node->hash);
        printf("node (%s, %lu) is not in table\n", node2->str, node2->hash);
    } else {
        SHOW_FAIL();
    }
}

void
test_table_remove(HashTable *table, Node *node, Node *node2)
{
    SHOW_TEST();

    table_dump(table);

    Node *ret;

    if ((ret = table_remove(table, node))) {
        printf("node (%s, %lu) is in table\n", ret->str, ret->hash);
        free(ret);
    } else {
        SHOW_FAIL();
        return;
    }

    if ((ret = table_remove(table, node2))) {
        SHOW_FAIL();
        return;
    } else {
        printf("node (%s, %lu) is not in table\n", node2->str, node2->hash);
    }

    table_dump(table);
}

int main (int argc, char **argv)
{
    // test node_create
    Node *node;
    node = test_node_create("abc");
    printf("\n");

    // test node_copy
    Node *copy;
    copy = test_node_copy(node);
    printf("\n");

    Node *node2;
    node2 = node_create("cba");

    // test node_get_hash            
    test_node_get_hash(node, copy, node2);
    printf("\n");

    // test node_get_hash_from_str
    test_node_get_hash_from_str(node, copy, node2);
    printf("\n");

    // test table_create
    HashTable *hash_table;
    hash_table = test_table_create(5);
    printf("\n");

    // test table_insert
    test_table_insert(hash_table, node);
    printf("\n");

    // test table_search
    test_table_search(hash_table, copy, node2);
    printf("\n");

    // test table_remove
    test_table_remove(hash_table, copy, node2);
}
