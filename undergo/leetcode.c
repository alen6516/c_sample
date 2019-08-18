#include <stdio.h>
#include <string.h>

void foo(char *str) {

    int str_len = strlen(str);
    int longest_len = 0;
    int position = 0;

    for (int i=0; i<str_len; i++) {
    
        int this_try_len = 0;

        if (*(str+i) == *(str+i+2) && i+2 < str_len) {
            this_try_len = 3;

            int n = 1;
            while (i-n >= 0 && i+2+n < str_len) {
                if (*(str+i-n) == *(str+i+2+n))
                    this_try_len += 2;
                else
                    break;
            }

        }
        else if (*(str+i) == *(str+i+1) && i+1 < str_len) {
            this_try_len = 2;
            int n = 1;
            while (i-n >= 0 && i+1+n < str_len) {
                if (*(str+i-n) == *(str+i+1+n))
                    this_try_len += 2;
                else
                    break;

            }
        
        }

        if (this_try_len > longest_len) {
            longest_len = this_try_len;
            position = i;
        }
    
    }

    printf("longest_len = %d\n", longest_len);
    printf("position = %d\n", position);

}


int main () {

    char str[] = "ababc";
    foo(str);


}
