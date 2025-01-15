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

// define dp[i][j] as the minimum number of operations required to convert the first i characters of string word1 to the first j characters of string word2
int minDistance(char *word1, char *word2)
{
    int m = strlen(word1);
    int n = strlen(word2);

    int dp[m+1][n+1];

    // i and j means current processed "length" of sub-word
    for (int i=0; i<=m; i++) {
        for (int j=0; j<=n; j++) {
            if (i == 0) {
                dp[i][j] = j;   // when word1 is empty, we need j insertions
            } else if (j == 0) {
                dp[i][j] = i;   // when word2 is empty, we need i deletions
            }
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int len;

    if (argc >= 2) {
        len = strtol(argv[1], NULL, 10);
    }
}
