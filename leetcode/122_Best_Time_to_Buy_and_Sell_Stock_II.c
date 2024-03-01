#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

int maxProfit(int* prices, int pricesSize) {

    int min, max;
    min = max = prices[0];
    int ret = 0;

    for (int i = 1; i< pricesSize; i++) {
        if (prices[i-1] > prices[i]) {
            if (max != min)
                ret += (max - min);
            min = max = prices[i];
        } else if (prices[i] > prices[i-1]) {
            max = prices[i];
        }
    }

    if (max != min)
        ret += (max-min);

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
