/* many adders add to a variable, and
 * many getters get and reset the variable
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ADDER_NUM 10
#define ADDER_COUNT 100000

_Atomic int _adder_id;
__thread int adder_id;

int count;
int adder_finish;

void* adder(void* arg)
{
    adder_id = ++ _adder_id;
    for (int i=0; i < ADDER_COUNT; i++) {
        __sync_fetch_and_add(&count, 1);
    }
    __sync_fetch_and_add(&adder_finish, 1);
    return NULL;
}

void* get_and_reset(void *arg)
{
    int sum = 0;
    int get = 0;
    int get_fail = 0;
    int finish = 0;

    while (1) {
        if (adder_finish == ADDER_NUM) {
            printf("finished\n");
            finish = 1;
        }

        do {
            if (++get_fail > 1) {
                printf("get fail = %d\n", get_fail);
            }
            get = count;
            sleep(0);
        } while(!__sync_bool_compare_and_swap(&count, get, 0));
        get_fail = 0;
        printf("get = %d\n", get);
        sum += get;
        if (finish) {
            break;
        }
    }
    printf("sum = %d\n", sum);
    printf("tot = %d\n", ADDER_NUM*ADDER_COUNT);
    return NULL;
}

int main()
{   
    srand(time(NULL));

    pthread_t adder_arr[ADDER_NUM];
    for (int i=0; i<ADDER_NUM; i++) {
        pthread_create(&adder_arr[i], NULL, adder, NULL);
    }

    pthread_t getter;
    pthread_create(&getter, NULL, get_and_reset, NULL);
    pthread_join(getter, NULL);
}
