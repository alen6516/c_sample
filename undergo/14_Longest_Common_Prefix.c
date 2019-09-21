#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * longestCommonPrefix(char ** strs, int strsSize) {

    char ret[50];
    int sum = 0;
    int pos = 0;

    for (; strs[0][pos] != '\0'; pos++) {
    
        for (int i=0; i<strsSize; i++) {
        
            sum += strs[i][pos];
            
        }
        if ( (sum / strsSize) == strs[0][pos]) {
            ret[pos] = strs[0][pos];
        } else {
            break;
        }
    }
    ret[pos] = '\0';
    
    size_t len = strlen(ret);
    printf("len = %d\n", (int)len);

    char *q;
    if (len == 0) {
        q = (char*) malloc(0);
        return q;
    } else {
    
        q = (char*) malloc (len+1);
        strncpy(q, ret, len);
        q[len] = '\0';
        return q;
    }



}

int main () {
    char *s[] = {"123", "12", "1234"};
    printf("%s\n", longestCommonPrefix(s, 3));
}
