#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char ** foo(char* str, char b) {
    
    int num = 0;

    for (int i=0; str[i] != 0; i++) {
        if (str[i] == b) {
            num++;
        }
    }
    num++;

    char *ret[num];

    int start = 0;
    char *one;
    int count = 0;

    for (int i=0; str[i] != 0; i++) {
        if (str[i] == b) {
            one = (char*) malloc (i-start+1);
            strncpy(one, str+start, i-start);
            one[i-start] = '\0';
            ret[count++] = one;
        }
    }

}


int main () {

    
}
