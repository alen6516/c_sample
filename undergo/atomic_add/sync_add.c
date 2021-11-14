#include <stdio.h>
#include <pthread.h>

extern __thread int count;  // per thread counter
static unsigned long a;     // global counter

static void *sync_add(void *arg)
{
    while ((count++) < *(int*)arg) {
        __sync_fetch_and_add(&a, 1);
    }
}

void test_sync_add(int thr_num, int add_num)
{
    pthread_t thr_arr[thr_num];

    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    for (int i=0; i < thr_num; i++) {
        pthread_create(&thr_arr[i], NULL, sync_add, (void*)&add_num);
        pthread_join(thr_arr[i], NULL);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("test_sync_add: ===============================\n");
    printf("a = %lu\n", a);
    printf("s = %lu\n", (unsigned long)thr_num * add_num);
    printf("Total time taken by CPU: %f sec\n", total_t);
}
