#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// Runtime 89 ms Beats 91.34% of users with C
// Memory 12.94 MB Beats 41.95% of users with C
int maxProfit(int* prices, int pricesSize) {

    int min, max;
    min = max = prices[0];
    int ret = 0;

    for (int i = 1; i< pricesSize; i++) {
        if (prices[i] > max && (prices[i] - min) > ret) {
            ret = prices[i] - min;
        } else if (prices[i] < min) {
            min = max = prices[i];
        }
    }
    return ret;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *arr;
    int len;
    int ret;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    } else {
        len = rand() % 5 + 10;
    }

    arr = arr_create(&len);
    arr_show(arr, len);

    ret = maxProfit(arr, len);
    printf("-------------\n");
    printf("max profit = %d\n", ret);
}
