#include <stdio.h>
#include <pthread.h>

extern __thread int count;  // per thread counter
static unsigned long a;     // global counter
static pthread_spinlock_t spin_lock;

static void *spin_lock_add(void *arg)
{
    while ((count++) < *(int*)arg) {
        pthread_spin_lock(&spin_lock);
        a++;
        pthread_spin_unlock(&spin_lock);
    }
}

void test_spin_lock_add(int thr_num, int add_num)
{
    pthread_t thr_arr[thr_num];
    pthread_spin_init(&spin_lock, PTHREAD_PROCESS_PRIVATE);

    clock_t start_t, end_t;
    double total_t;

    start_t = clock();
    for (int i=0; i < thr_num; i++) {
        pthread_create(&thr_arr[i], NULL, spin_lock_add, (void*)&add_num);
        pthread_join(thr_arr[i], NULL);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("test_spin_lock_add: ==========================\n");
    printf("a = %lu\n", a);
    printf("s = %lu\n", (unsigned long)thr_num * add_num);
    printf("Total time taken by CPU: %f sec\n", total_t);
}
