#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 20


struct node_t {
    int key;
    int val;
    struct node* next;
};


struct node_t* hashArray[SIZE];
struct node_t* dummyNode;
struct node_t* node;


int get_key();
void insert();
struct node_t* search();
void delete();


int _get_key(char *s) {
    int ret = 0;
    for (int i=0; i<strlen(s); i++) {
        (*(s+i))
    }
}

int get_key(char *s) {
    
    


    return key % SIZE;
}


struct note_t* search(int key) {

    int hashIndex = get_key(key);



}
