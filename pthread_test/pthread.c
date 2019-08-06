#include <stdio.h>
#include <pthread.h>

typedef struct my_data {
    int a;
    int b;
    int result;
} my_data;

void *child(void *arg) {
    my_data *data = (my_data *)arg;
    data->result = data->a + data->b;
    pthread_exit(NULL);
}

int main() {
    pthread_t t;
    my_data data;

    data.a = 1;
    data.b = 2;

    pthread_create(&t, NULL, child, &data);

    pthread_join(t, NULL);

    printf("%d + %d = %d\n", data.a, data.b, data.result);
    
    return 0;
}
