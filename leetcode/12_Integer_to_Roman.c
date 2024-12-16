/*
Runtime: 4 ms, faster than 85.96% of C online submissions for Integer to Roman.
Memory Usage: 7 MB, less than 80.00% of C online submissions for Integer to Roman.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * intToRoman(int num) {

    char ret[50];
    int curr_len = 0;
    int curr = 0;

    // 1000
    if ( (curr = num / 1000) ) {
    
        for (int i=0; i<curr; i++) {
            ret[curr_len++] = 'M';
        }
        num %= 1000;
    }
    

    // 100
    if ( (curr = num / 100) ) {
    
        if (curr < 4) {
            for (int i=0; i<curr; i++) {
                ret[curr_len++] = 'C';
            }

        } else if (curr == 4) {
            ret[curr_len++] = 'C';
            ret[curr_len++] = 'D';

        } else if (curr < 9) {
            ret[curr_len++] = 'D';
            for (int i=5; i<curr; i++) {
                ret[curr_len++] = 'C';
            }
        } else if (curr == 9) {
            ret[curr_len++] = 'C';
            ret[curr_len++] = 'M';
        }
        num %= 100;
    }

    // 10
    if ( (curr = num / 10) ) {
    
        if (curr < 4) {
            for (int i=0; i<curr; i++) {
                ret[curr_len++] = 'X';
            }

        } else if (curr == 4) {
            ret[curr_len++] = 'X';
            ret[curr_len++] = 'L';

        } else if (curr < 9) {
            ret[curr_len++] = 'L';
            for (int i=5; i<curr; i++) {
                ret[curr_len++] = 'X';
            }
        } else if (curr == 9) {
            ret[curr_len++] = 'X';
            ret[curr_len++] = 'C';
        }
        num %= 10;
    }


    // 1
    if ( (curr = num) ) {
    
        if (curr < 4) {
            for (int i=0; i<curr; i++) {
                ret[curr_len++] = 'I';
            }

        } else if (curr == 4) {
            ret[curr_len++] = 'I';
            ret[curr_len++] = 'V';

        } else if (curr < 9) {
            ret[curr_len++] = 'V';
            for (int i=5; i<curr; i++) {
                ret[curr_len++] = 'I';
            }
        } else if (curr == 9) {
            ret[curr_len++] = 'I';
            ret[curr_len++] = 'X';
        }
    }


    ret[curr_len] = '\0';
    char *q = (char*) malloc(sizeof(char)*(curr_len+1));
    strcpy(q, ret);
    return q;
}

int main () {
   printf("%s\n", intToRoman(1994) );

}
