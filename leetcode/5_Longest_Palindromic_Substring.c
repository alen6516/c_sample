/* 
Runtime: 20 ms, faster than 64.85% of C online submissions for Longest Palindromic Substring.
Memory Usage: 6.1 MB, less than 72.47% of C online submissions for Longest Palindromic Substring.

Solution: use a for loop to go through the string, detect 2 kinds of Palindromic Substring
    1. str[i] == str[i+1], then use a while loop to expand and detect
    2. str[i] == str[i+2], also use a while loop to expand and detect

Improve: based on this method, thinking if we can skip some char when going through the string.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* foo(char *str) {

	int str_len = strlen(str);

    
    int longest_len = 1;	// the longest string currently detected, note shortest len is 1
    int position = 0;		// this substring start from which index

    int i;
    for (i=0; i<str_len; i++) {
        //printf("i=%d\n", i);
        int this_try_len = 0;
        int n = 0;

		// for case "babad"
        if (i+2 < str_len && *(str+i) == *(str+i+2)) {
            this_try_len = 3;
            n = 1;

            while (i-n >= 0 && i+2+n < str_len) {
                if (*(str+i-n) == *(str+i+2+n)) {
                    this_try_len += 2;
                    n++;
                }
                else {
                    
                    break;
                }
            }
            if (this_try_len > longest_len) {
                longest_len = this_try_len;
                position = i-n+1;		// +1 to push back the final n++
            }

        }

		// for case "baab"
		// note do not use else if, think of case "cccc"
        if (i+1 < str_len && *(str+i) == *(str+i+1)) {
            this_try_len = 2;
            n = 1;
            while (i-n >= 0 && i+1+n < str_len) {
                if (*(str+i-n) == *(str+i+1+n)) {
                    this_try_len += 2;
                    n++;
                }
                else {
                    
                    break;
                }   
            }
            if (this_try_len > longest_len) {
                longest_len = this_try_len;
                position = i-n+1;
            }
        }

        
    }

    if (str_len == longest_len) {
        return str;
    }

    char *ret = (char*)malloc(longest_len+1);
    strncpy(ret, str+position, longest_len);
    ret[longest_len] = '\0';
}


int main (int argc, char *argv[]) {
	
	char str[] = "babad";
    printf("%s\n", foo(str));


}
