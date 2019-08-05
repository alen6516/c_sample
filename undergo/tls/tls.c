/***
 File Name: tls.c
 Author: alen6516
 Created Time: 2019-08-05
***/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int counter = 0;


void *foo(void *arg) {
    int *tid = (int*) arg;

    while (1) {
        counter++;
        printf("id = %d, counter = %d\n", *tid, counter);
        sleep(1);
    }
}


typedef struct test {
    int a1 = 0;
} test;




int main () {

    pthread_t t1, t2;

    int a = 1, b = 2;


    pthread_create(&t1, NULL, foo, &a);
    pthread_create(&t2, NULL, foo, &b);
    
    pthread_join(t2, NULL);


}
