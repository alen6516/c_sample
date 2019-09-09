#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

#define DEBUG 1
char debug_buff[50];

#define SIZE 31

struct node_t {
    int code;
    char* val;
    struct node_t* insert_next;
    struct node_t* search_next;
};


struct node_t* hashArray[SIZE] = { NULL };
struct node_t* dummyNode;
struct node_t* node;


int get_key();
void insert();
//struct node_t* search();
//void delete();


int get_code(char *s) {
    int ret = 0;
    int len = strlen(s);
    for (int i=0; i<len; i++) {
        //ret += ( (*(s+i))<<(len-1-i) );
        ret += ( *(s+i) << i );
    }

    
    sprintf(debug_buff, "code = %d\n", ret);
    /**_debug(__func__, debug_buff);*/
    printf("%s: %s", __func__, debug_buff);
    return ret;
}

int get_key(int code) {
    
    return code % SIZE;

}


void insert(char *val) {

    struct node_t* node = (struct node_t*) malloc(sizeof(struct node_t));
    node->code = get_code(val);
    node->val = val;
    node->insert_next = NULL;
    node->search_next = NULL;


    int this_key = get_key(node->code);
    node_t* this_node = hashArray[this_key];

    if (this_node) {
        
        this_node->insert_next = node;
        node->search_next = this_node;
        hashArray[this_key] = node;
    
    } else {
    
        hashArray[this_key] = node;
    }

}


struct node_t* search(char* val) {
    
    int this_code = get_code(val);
    int this_key = get_key(this_code);

    node_t* this_node = hashArray[this_key];

    while (this_node->search_next) {

        if (this_code == this_node->code && 
            strcmp(val, this_node->val)) {
            
            return this_node;
            
        } else {
            this_node = this_node->search_next;
        }
    }

    return NULL;
}


int main () {
    
    char s[] = "abc";
    insert(s);

}
