#ifndef NODE_H
#define NODE_H

typedef unsigned char   u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;


typedef struct node_base_t {
    void *next;
} NODE_BASE_T;

struct job_node_t {
    struct node_base_t base;
    int val;
} __attribute__((packed));

void* node_get_next(struct node_base_t* base) {
    return base->next;
}


#endif
