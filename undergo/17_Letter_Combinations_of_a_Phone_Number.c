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

    int len = strlen(digits);   // size of the input string
    int arr_len = 1;            // size of the return array

    printf("digits = %s\n", digits);
    for (int i=0; i<len; i++) {
        printf("%c = \"%s\"\n", digits[i], letter[digits[i]-('1'-1)]);
    }

    for (int i=0; i<len; i++) {
        arr_len *= strlen(letter[digits[i]-('1'-1)]);
    }

    printf("arr_len = %d\n", arr_len);

    int parr[len];              // position array, length is the size of the input string
    memset(parr, 0, sizeof(parr));

    // alloc for return array
    char **ret = (char**) malloc(sizeof(char*)*arr_len);

    char *str;
    int finish = 0;

    do {
        // fill string with the prepared parr
        str = (char*) malloc(sizeof(char)*(len+1));
        for (int w=0; w<len; w++) {
            str[w] = *letter[digits[w]-('1'-1)]+parr[w];
        }
        ret[finish++] = str;
        if (finish == arr_len) {
            break;
        }

        // prepare
        for (int p=0; p<len; p++) {
            if (parr[p] +1 == strlen(letter[digits[p]-('1'-1)])) {
                parr[p] = 0;
                continue;
            } else {
            
                parr[p] ++;
                break;
            }
        }
    } while (1);
    
    for (int i=0; i<arr_len; i++) {
        printf("%s\n", ret[i]);
    }

    exit(0);

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