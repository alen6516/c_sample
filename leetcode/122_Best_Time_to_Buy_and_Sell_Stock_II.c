#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

// Runtime 3 ms Beats 85.66% of users with C
// Memory 6.73 MB Beats 40.95% of users with C
int maxProfit(int* prices, int pricesSize) {

    if (pricesSize == 1) return 0;

    int max, min;
    max = min = prices[0];
    int ret = 0;

    for (int i = 1; i< pricesSize; i++) {
        if (prices[i-1] > prices[i]) {          // peak
            if (max != min)
                ret += (max - min);
            min = max = prices[i];
        } else if (prices[i] > prices[i-1]) {   // bottom
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
    //arr_show(arr, len);

    int arr2[] = {8,6,4,3,3,2,3,5,8,3,8,2,6};
    len = 13;
    arr_show(arr2, len);

    ret = maxProfit(arr2, len);
    printf("-------------\n");
    printf("max profit = %d\n", ret);
}
