#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int myAtoi(char * s) {

    int len = strlen(s);
    char is_positive = -1;      // -1 for uninit, 0 for -, 1 for +
    int ret = 0;

    for (int i=0; i<len; i++) {

        if (is_positive == -1) {

            if (s[i] == ' ')
                continue;
            
            if (s[i] == '-') {
                is_positive = 0;
                continue;
            
            } else if (s[i] == '+') {
                is_positive = 1;
                continue;

            } else if ((s[i] >= '0' && s[i] <= '9')) {
                is_positive = 1;
            
            } else {
                return 0;
            }

        } 
        if ( !(s[i] >= '0' && s[i] <= '9') )
            break;


        if (is_positive) {

            if ( (INT_MAX/10 >= ret) && 
                 (INT_MAX - (s[i]-'0') >= ret*10 ) ) {
                ret = ret*10 + (s[i]-'0');
            } else return INT_MAX;


        } else {

            if ( (INT_MIN/10 <= ret) && 
                 (INT_MIN + (s[i]-'0') <= ret*10 ) ) {
                ret = ret*10 - (s[i]-'0');
            } else return INT_MIN;
        }
    }
    return ret;
}

int main () {

    char s[] = "2147483648";
    printf("input : %s\n", s);
    printf("result: %d\n", myAtoi(s));

    char s1[] = "-2147483649";
    printf("input : %s\n", s1);
    printf("result: %d\n", myAtoi(s1));
}
