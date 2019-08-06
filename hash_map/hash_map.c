#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// struct of Data
typedef struct {
    int key;
    int val;
} Data_t;


// struct of Node
typedef struct {
    Data_t data;
    struct Node_t *next;    // use link when key conflict
} Node_t;


// struct of Map
typedef struct {
    int size;
    Node_t *table;
} Map_t;


Map_t *create_map (int *nums, int size) {
    
    // Allocate for map
    Map_t *map = (Map_t*) malloc(sizeof(Map_t));
    map->size = 2*size;


    // Allocate for table
    map->table = (Node_t*) malloc(sizeof(Node_t) * map->size);


    // init
    for (int j=0; j < map->size; j++) {
        map->table[j].data.val = INT_MIN;
        map->table[j].next = NULL;
    }


    // build hash_map
    int i = 0;
    while (i < size) {
        
        // count index
        int pos = abs(nums[i]) % map->size;


        // determine if conflict
        if (map->table[pos].data.key == INT_MIN) {
            // No conflict
            
            // let index as key
            map->table[pos].data.key = i;

            // let val as val
            map->table[pos].data.val = nums[i];
        }

        else {
            // conflict
            
            // give curr data a Node and copy the node
            Node_t *lnode = (Node_t*) malloc(sizeof(Node_t));
            Node_t *node;

            lnode->data.key = i;
            lnode->data.val = nums[i];
            lnode->next = NULL;


            // iterate list from the conflicted node
            node = &(map->table[pos]);
            while (node->next != NULL) {
                node = node->next;
            }
            // link curr node to the lsit
            node->next = lnode;
        }
        // handle the next one
        i++;
    }
    return map;
}


int get_node (Map_t map, int val) {
    
    // calculate position according to the val
    int pos = abs(key) % map.size;

    Node_t *p = &(map.table[pos]);

    // search
    while (p != NULL) {
        if (p->data.val == val)
            return p->data.key;
        else
            p = p->next;
    }

    // return -1 if no hit
    return -1;
}
