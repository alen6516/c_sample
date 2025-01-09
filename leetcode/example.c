/**
 * Description
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils/arr.h"
#include "utils/utils.h"

#define ARR_SIZE(arr) (int)sizeof(arr)/sizeof(arr[0])

#define SWAP(a, b) do {     \
    a = a^b;                \
    b = a^b;                \
    a = a^b;                \
} while (0)

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    }
}
