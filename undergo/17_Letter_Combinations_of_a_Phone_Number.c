#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int len = strlen(digits);
    int arr_len = 1;

    for (int i=0; i<len; i++) {
        arr_len *= strlen(letter[digits[i]-('1'-1)]);
    }

    printf("arr_len = %d\n", arr_len);

    int parr[len];
    memset(parr, 0, sizeof(parr));

    // alloc for return array
    char **ret = (char**) malloc(sizeof(char*)*arr_len);

    
    for (int i=0; i<arr_len; i++) {

        // alloc for each string
        ret[i] = (char*) malloc(sizeof(char)*(len+1));

        // fill each string by parr
        for (int j=0; j<len; j++) {
            ret[i][j] = letter[digits[j]-('1'-1)][parr[j]];
        }
        ret[i][len] = '0';

        // add 1 and check if carry
        for (int k=0; k<len; k++) {
            if (parr[k]+1 < strlen(letter[digits[k]-('1'-1)])) {
                parr[k] += 1;
            } else {
                parr[k] = 0;
            }
        }
    }

    for (int i=0; i<arr_len; i++) {
        printf("%s\n", ret[i]);
    }

    exit(0);

}

int main ()
{

    const char *digit = "29";
    int returnSize = 0;

    char **ret = letterCombinations((char*)digit, &returnSize);


    printf("Output: [");
    for (int i=0; i<returnSize; i++) {
        printf("\"%s\", ", ret[i]);
    }
    printf("]");
}
