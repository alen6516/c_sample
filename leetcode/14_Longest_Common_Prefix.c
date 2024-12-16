/*
Runtime: 0 ms, faster than 100.00% of C online submissions for Longest Common Prefix.
Memory Usage: 7.1 MB, less than 87.50% of C online submissions for Longest Common Prefix.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char * longestCommonPrefix(char ** strs, int strsSize) {


    if (strsSize == 0) {
        return "";
    } else if (strsSize == 1) {
        return strs[0];
    }

    unsigned short pos = 0;
    unsigned short i;
    bool flag = true;

    while (flag) {
        i = 0;
        while (i < strsSize-1) {
            if (strs[i][pos] != '\0' && strs[i][pos] == strs[i+1][pos]) {
                i++;
                continue;
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            pos++;
        }
    }

    char *q;
    q = (char*) malloc (pos+1);
    if (pos != 0) {
        strncpy(q, strs[0], pos);
    }
    q[pos] = '\0';
    return q;

}

