// 5. Longest Palindromic Substring

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

	char ret[1001] = {0};		// assume the larget str is 1000 len, add 1 for \0
	strncpy(ret, str+position, longest_len);
	ret[longest_len] = '\0';

	//printf("len = %d\n", str_len);
    printf("longest = %d, position = %d\n", longest_len, position);
	

	char *a = ret;
	return a;		// return ret on leetcode causes error, I don't know why
}


int main (int argc, char *argv[]) {
	
	char str[] = "babad";
    printf("%s\n", foo(str));


}
