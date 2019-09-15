#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myAtoi(char * s) {

    int len = strlen(s);
    char sign = -1;      // -1 for uninit, 0 for -, 1 for +
    int ret = 0;

    for (int i=0; i<len; i++) {

        if (sign == -1) {

            if (s[i] == ' ')
                continue;
            
            if (s[i] == '-') {
                sign = 0;
                continue;
            
            } else if (s[i] == '+') {
                sign = 1;
                continue;

            } else if (s[i] == '+' || (s[i] >= '0' && s[i] <= '9')) {
                sign = 1;
            
            } else {
                return 0;
            }
        } 
        if ( !(s[i] >= '0' && s[i] <= '9') )
            break;

        ret = ret * 10 + (s[i] - '0');
        
    }
    return ret;
}

int main () {


}
