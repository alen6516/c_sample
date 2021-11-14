#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

__thread int count;

extern void test_atomic_type_add(int, int);
extern void test_atomic_long_add(int, int);
extern void test_sync_add(int, int);
extern void test_atomic_add(int, int);
extern void test_mutex_lock_add(int, int);
extern void test_spin_lock_add(int, int);
extern void test_spin_trylock_add(int, int);

int main (int argc, char *argv[])
{
    int thr_num = 1000;
    int add_num = 1000;

    if (argc == 3) {
        thr_num = (int) strtol(argv[1], NULL, 10);
        add_num = (int) strtol(argv[2], NULL, 10);
    }

    printf("thead number: %d\n", thr_num);
    printf("per thrd add: %d\n", add_num);

    test_atomic_type_add(thr_num, add_num);
    test_atomic_long_add(thr_num, add_num);
    test_sync_add(thr_num, add_num);
    test_atomic_add(thr_num, add_num);
    test_mutex_lock_add(thr_num, add_num);
    test_spin_lock_add(thr_num, add_num);
    test_spin_trylock_add(thr_num, add_num);
}
