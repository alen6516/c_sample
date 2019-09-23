#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char * longestCommonPrefix(char ** strs, int strsSize) {

    if (strsSize == 0 || strlen(strs[0]) == 0) {      
        return "";
    } else if (strsSize == 1) {
        return strs[0];
    }
    
    char ret[50];
    int pos = 0;
    int i;
    int flag = 1;

    while (flag) {
        i = 0;
        while (i < strsSize-1) {
            if (strs[i][pos] != '\0' && strs[i+1][pos] != '\0' && strs[i][pos] == strs[i+1][pos]) {
                continue;
            } else {
                flag = 0;
                break;
            }
        }
        if (flag) {
            ret[pos] = strs[0][pos];
            pos++;
        }
    }

    if (pos == 0)
        return "";
    else
        ret[pos] = '\0';

    char *q;
    q = (char*) malloc (pos+1);
    strcpy(q, ret);
    return q;

}

int main () {
}
