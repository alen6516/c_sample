#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myAtoi(char * s) {

    int len = strlen(s);
    
    char sign = 0;      // 0 for -, 1 for +

    int start_off = 0;
    int end_off = 0;

    for (int i=0; i<len; i++) {
    
        if (s[i] == ' ')
            continue;
        
        if (s[i] == '-') {
        }
        
        else if (s[i] == '+' || (s[i] >= 0 && s[i] <= 9)) {
            sign = 1;
        } else {
            return 0;
        }

        start_off = i;



    }

}

int main () {


}
