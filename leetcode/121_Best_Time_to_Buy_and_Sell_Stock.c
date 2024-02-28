#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

int maxProfit(int* prices, int pricesSize) {
    int min_id, max_id;
    min_id = max_id = 0;
    int ret = 0;

    for (int i = 1; i< pricesSize; i++) {
        if (prices[i] > prices[min_id]) {
            // find a valid max
            if (prices[i] > prices[max_id]) {
                max_id = i;
                if (prices[max_id] - prices[min_id] > ret) {
                    ret = prices[max_id] - prices[min_id];
                    printf("find new (%d, %d) = %d\n", min_id, max_id, ret);
                }
            }
        } else if (prices[i] < prices[min_id]) {
            
        }
    }
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

    return 0;
    ret = maxProfit(arr, len);
    printf("-------------\n");
    printf("max profit = %d\n", ret);
}
