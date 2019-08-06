#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *child() {
    for (int i = 0; i<3; ++i) {
        pthread_mutex_lock( &mutex1 );
        int tmp = counter;
        sleep(1);
        counter = tmp + 1;
        pthread_mutex_unlock( &mutex1 );
        printf("counter = %d\n", counter);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, child, NULL);
    pthread_create(&t2, NULL, child, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
