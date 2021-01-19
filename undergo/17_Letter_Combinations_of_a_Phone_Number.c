#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize)
{

    static const char * letter[] = {
        [1] = "",
        [2] = "abc",
        [3] = "def",
        [4] = "ghl",
        [5] = "jkl",
        [6] = "mno",
        [7] = "pqrs",
        [8] = "tuv",
        [9] = "wxyz",
    };

}

int main ()
{

    const char *digit = "23";
    int returnSize = 0;

    char **ret = letterCombinations((char*)digit, &returnSize);


    printf("Output: [");
    for (int i=0; i<returnSize; i++) {
        printf("\"%s\", ", ret[i]);
    }
    printf("]");
}
