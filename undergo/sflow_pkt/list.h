#ifndef NODE_H
#define NODE_H

#include "util.h"
#include <stdlib.h>

#define NODE_CALLOC() \
    do { \
        (struct node_t*) calloc(1, sizeof(struct node_t)); \
    while(0)

struct node_t {
    u8 type; // 1 for icmpv4, 17 for udp
    u32 sip;
    u32 dip;
    u16 sport;
    u16 dport;
    struct node_t *next;
} __attribute__((packed));;


#endif
