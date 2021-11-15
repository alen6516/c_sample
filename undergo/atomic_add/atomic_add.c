#include <stdio.h>
#include <pthread.h>

extern __thread int count;  // per thread counter
static unsigned long a;     // global counter

static void *atomic_add(void *arg)
{
    while ((count++) < *(int*)arg) {
        __atomic_add_fetch(&a, 1, 0);
    }
}

void test_atomic_add(int thr_num, int add_num)
{
    pthread_t thr_arr[thr_num];

    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    for (int i=0; i < thr_num; i++) {
        pthread_create(&thr_arr[i], NULL, atomic_add, (void*)&add_num);
        pthread_join(thr_arr[i], NULL);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("test_atomic_add: =============================\n");
    printf("a = %lu\n", a);
    printf("s = %lu\n", (unsigned long)thr_num * add_num);
    printf("Total time taken by CPU: %f sec\n", total_t);
}
