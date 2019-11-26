#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "list.h"

int getRandNum() {
    FILE *fp;
    if ((fp = fopen("/dev/urandom", "r")) == NULL) {
       fprintf(stderr, "Error!, Could not open /dev/urandom to read.\n");
       return -1;
    }

    int result = fgetc(fp);
    return result;
}

void* foo(void* _id) {

    sleep(getRandNum()%7);
    thr_list_push(*((int*)_id), thr_list);

    printf("\tafter push, tail id = %d\n", thr_list->tail_id);

    return NULL;
}



void handler(int sig_num) {

    int id;
    id = thr_list->head_id;
    
    if (id == -1) {
        printf("no ava thread\n");
        return;
    }
    printf("ava list: %d", id);
    id = thr_arr[id].next_id;

    while (-1 != id) {
        printf(" -> %d", id);
        id = thr_arr[id].next_id;
    }
    printf("\n");
}


int main () {

    
    thr_list = (struct thr_list_t*) init_thr_list();
    if (NULL == thr_list) {
        printf("error\n");
        return 1;
    }

    signal(SIGTSTP, handler);

    int id;
    while (1) {
        
        id = thr_list_pop(thr_list);
        if (-1 == id) {
            printf("pop fail, no ava thr\n");
        } else {
            printf("pop id = %d\n", id);
            pthread_create(&(thr_arr[id].thr), NULL, foo, &(thr_arr[id].my_id));
            printf("after pop, ");
            handler(0);
        }

        sleep(getRandNum()%5);
    }

}
