#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "work_list.h"

int getRandNum() {
    FILE *fp;
    if ((fp = fopen("/dev/urandom", "r")) == NULL) {
       fprintf(stderr, "Error!, Could not open /dev/urandom to read.\n");
       return -1;
    }

    int result = fgetc(fp);
    return result;
}

struct node_t {
    int a;
    struct node_t* next;
};

struct list_t* list;


void* read_work(void* arg) {
    int i=0;
    int len = 20;
    void* tmp = NULL;
    while(i<len) {
        while (list->head) {
            printf("pop %d\n", ((struct node_t*)(list->head))->a);
            tmp = list->head;
            list->head = (void*)((struct node_t*)list->head)->next; 
            free(tmp);
            i++;
        }
        sleep(getRandNum()%8);

    }
    return NULL;
}


void* write_work(void* arg) {
    int arr[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int len = 20;


    struct node_t* node;
    for (int i=0; i<len; i++) {
        node = (struct node_t*)malloc (sizeof(struct node_t));
        bzero(node, sizeof(struct node_t));
        node->a = arr[i];
        printf("push %d\n", node->a);
        list_push((void*)node,(void**) &(node->next), list);
        sleep(getRandNum()%3);
    }
    return NULL;
}

int main () {

    pthread_t rt, wt;
    list = (struct list_t*) list_init();
    pthread_create(&wt, NULL, write_work, NULL);
    printf("writer created\n");
    pthread_create(&rt, NULL, read_work, NULL);
    printf("reader created\n");
    pthread_join(rt, NULL);

}
