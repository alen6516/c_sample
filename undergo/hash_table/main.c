#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 31

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
//struct node_t* search();
//void delete();


int _get_key(char *s) {
    int ret = 0;
    int len = strlen(s);
    for (int i=0; i<len; i++) {
        //ret += ( (*(s+i))<<(len-1-i) );
        ret += ( *(s+i) << i );
    }
    printf("code = %d\n", ret);
    return ret;
}

int get_key(char *s) {
    
    int key = _get_key(s);
    return key;
}


struct note_t* search(int key) {
    return NULL;
}


int main () {
    
    char s[] = "abc";
    get_key(s);

}
