/*
 * Runtime: 0 ms, faster than 100.00% of C online submissions for Letter Combinations of a Phone Number.
 * Memory Usage: 5.7 MB, less than 90.77% of C online submissions for Letter Combinations of a Phone Number.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize)
{
    static const char * letter[] = {
        [2] = "abc",
        [3] = "def",
        [4] = "ghl",
        [5] = "jkl",
        [6] = "mno",
        [7] = "pqrs",
        [8] = "tuv",
        [9] = "wxyz",
    };

    unsigned char digi_len = strlen(digits);   // size of the input string
    
    if (digi_len == 0) {
        *returnSize = 0;
        return (char**)0;
    }

    int arr_len = 1;                // size of the return array

    // debug
    //printf("digits = %s\n", digits);
    //for (int i=0; i<digi_len; i++) {
    //    printf("%c = \"%s\"\n", digits[i], letter[digits[i]-('1'-1)]);
    //}

    // get return arr size
    for (int i=0; i<digi_len; i++) {
        arr_len *= strlen(letter[digits[i]-('1'-1)]);
    }
    *returnSize = arr_len;

    //printf("returnSize = %d\n", *returnSize);

    unsigned char parr[digi_len];               // position array, length is the size of the input string
                                                // record the target letter in the strings of letters
    memset(parr, 0, sizeof(parr));

    // alloc for return array
    char **ret = (char**) malloc(sizeof(char*)*arr_len);

    char *str;                  // each string in return arr
    unsigned char finish = 0;   // how many strings have been finished

    do {
        // fill string with the prepared parr
        str = (char*) malloc(sizeof(char)*(digi_len+1));
        for (int w=0; w<digi_len; w++) {
            str[w] = *letter[digits[w]-('1'-1)]+parr[w];          
        }
        str[digi_len] = '\0';
        ret[finish++] = str;
        if (finish == arr_len) {
            break;
        }

        // prepare parr
        for (int p=0; p<digi_len; p++) {
            if (parr[p] +1 == strlen(letter[digits[p]-('1'-1)])) {
                parr[p] = 0;
                continue;
            } else {
                parr[p] ++;
                break;
            }
        }
    } while (1);

    // debug
    //for (int i=0; i<arr_len; i++) {
    //    printf("%s\n", ret[i]);
    //}
    
    return ret;
}

int main ()
{

    const char *digit = "2";
    int returnSize = 0;

    char **ret = letterCombinations((char*)digit, &returnSize);


    printf("Output: [");
    for (int i=0; i<returnSize; i++) {
        printf("\"%s\", ", ret[i]);
    }
    printf("]");
}
