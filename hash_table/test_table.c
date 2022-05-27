#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../util/util.h"
#include "hash_table.h"

/*
 * Read strings from text file and create a node list to contain the strings.
 *
 * Create a hash table to insert nodes from the node list.
 *
 * Check if the result is correct.
 *
 * Measure time consumption of the whole insertion.
 */


#define SIZE 7

int main (int argc, char **argv)
{
    // init fp to read strings from file
    FILE *fp = NULL;
    fp = fopen("text", "r");
    if (!fp) {
        perror("fail to open the file\n");
        return -1;
    }

    // init node list to store the strings
    int count = 0;
    Node *curr;
    Node dummy_insert, dummy_remove;
    Node **insert_next, **remove_next;
    insert_next = &dummy_insert.next;
    remove_next = &dummy_remove.next;

    char *line = NULL;      // string pointer
    size_t _len = 0;        // dummy
    ssize_t len;            // length of the read string

    // copy string to node list
    while (-1 != (len = getline(&line, &_len, fp))) {

        line[len-1] = 0;    // to replace newline
        curr = node_create(line);

        // before next
        count ++;
        *insert_next = curr;
        insert_next = &(*insert_next)->next;
        //if (count % 2) {
            *remove_next = node_copy(curr);
            remove_next = &(*remove_next)->next;
        //}
    }
    *insert_next = NULL;
    *remove_next = NULL;
    printf("total insert %d nodes\n", count);

    printf("insert list:\n");
    node_show_list(dummy_insert.next);
    printf("remove list:\n");
    node_show_list(dummy_remove.next);

    // init table
    HashTable *hash_table;
    hash_table = table_create(SIZE);

    // insert nodes to table
    Node *next;
    curr = dummy_insert.next;

    CLOCK_START();
    while (curr) {
        next = curr->next;
        if (NULL == table_insert(hash_table, curr)) {
            printf("fail to insert %s\n", curr->str);
        }
        curr = next;
    }
    CLOCK_END();

    printf("totally use %ld cycle to insert nodes\n", CLOCK_DIFF());
    table_dump(hash_table);

    printf("\n");
    printf("\n");

    // remove nodes from table
    curr = dummy_remove.next;
    
    CLOCK_START();
    while (curr) {
        next = curr->next;
        if (NULL == table_remove(hash_table, curr)) {
            printf("fail to remove %s\n", curr->str);
        }
        curr = next;
    }
    CLOCK_END();

    printf("totally use %ld cycle to remove nodes\n", CLOCK_DIFF());
    table_dump(hash_table);
}
