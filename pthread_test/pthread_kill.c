#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>
#include <pthread.h>

void handler(int sig_number) {

    printf("get %d, thread exit\n", sig_number);
    pthread_exit(0);
}

void* foo(void* a) {
    printf("thread start\n");
    signal(SIGUSR1, &handler);
    while(1) {
    }
    return NULL;
}

int main () {

    pthread_t t;
    pthread_create(&t, NULL, foo, NULL);
    sleep(3);
    pthread_kill(t, SIGUSR1);
    pthread_join(t, NULL);
    printf("main thread leave\n");
}
