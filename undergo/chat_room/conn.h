#ifndef CONN_H
#define CONN_H

#include <stdlib.h>
#include <string.h>

typedef struct __conn {
    int fd;
    char name[10];
    struct __conn* next;
} conn_t;

conn_t* init_conn(int fd) {
    conn_t* ret = (conn_t*) malloc(sizeof(conn_t));
    if (ret) {
        ret->fd = fd;
        bzero(ret->name, sizeof(ret->name));
    }
    return ret;
}

int conn_get_key(void *conn) {
    if (!conn) return -1;
    return ((conn_t*) conn)->fd;
}

void* conn_get_next(void *conn) {
    if (!conn) return NULL;
    return ((conn_t*) conn)->next;
}

int conn_match(void *conn, int in_fd) {
    if (!conn) return -1;
    return ((conn_t*) conn)->fd == in_fd;
} 

int conn_link(void *a, void *b) {
    if (!a) return -1;
    ((conn_t*) a)->next = (conn_t*)b;
    return 0;
}


#endif
