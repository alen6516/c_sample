#ifndef CLIENT_TABLE_H
#define CLIENT_TABLE_H

#define CLIENT_TABLE_BUCKET_SIZE 32

#include "util.h"

typedef struct cli_conn {
    union {
        u32 key;
        u32 fd;
    };
    char name[10];
    struct cli_conn* next;
} cli_conn_t;

extern cli_conn_t *cli_conn_bucket[CLIENT_TABLE_BUCKET_SIZE];

u32  client_conn_hash(u32);
void client_conn_insert(cli_conn_t *);
cli_conn_t* client_conn_lookup(u32);
u8  client_conn_remove(u32);

#endif 
