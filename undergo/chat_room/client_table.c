#include <stdio.h>
#include <stdlib.h>
#include "client_table.h"
#include "util.h"

cli_conn_t *cli_conn_bucket[CLIENT_TABLE_BUCKET_SIZE] = {0};

u32 client_conn_hash(u32 key)
{
    return (key % CLIENT_TABLE_BUCKET_SIZE);
}

void client_conn_insert(cli_conn_t *cli_conn)
{
    u32 bucket = client_conn_hash(cli_conn->key);
    cli_conn->next = cli_conn_bucket[bucket];
    cli_conn_bucket[bucket] = cli_conn;
}

cli_conn_t* client_conn_lookup(u32 key)
{
    u32 bucket = client_conn_hash(key);
    cli_conn_t *curr = cli_conn_bucket[bucket];
    while (curr) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

cli_conn_t* client_conn_remove(u32 key)
{
    u32 bucket = client_conn_hash(key);
    cli_conn_t *curr = cli_conn_bucket[bucket];
    cli_conn_t *prev = NULL;
    while (curr) {
        if (curr->key == key) {
            if (prev) {
                prev->next = curr->next;
            } else {
                cli_conn_bucket[bucket] = NULL;
            }
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}
