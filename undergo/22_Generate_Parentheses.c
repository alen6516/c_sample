/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// start: first char*'s addr
// offset: the num of char we have
void subroutine(char **start, int *offset, const char* pattern, int n, int right, int left)
{
    // fill (
    start[*offset] = (char*) malloc(n+1);
    if (pattern[0]) {
        strncpy(start[*offset], pattern, n-right-left);
    }
    start[*offset][n-right-left] = '(';
    *offset += 1;
    left --;

    if (left > 0) {
        // next can fill ( or )
        subroutine(start, offset, (const char*)start[(*offset)-1], n, right, left);
    } else {
        // only can fill )
        memset(start[(*offset)-1], ')', right);
        start[(*offset)-1][n] = '\0';
        printf("%s\n", start[(*offset)-1]);
    }

    // fill )
    if (right == 0 || left > right) {
        return;
    }

    start[*offset] = (char*) malloc(n+1);
    if (pattern[0]) {
        strncpy(start[*offset], pattern, n-right-left);
    }
    start[*offset][n-right-left] = ')';
    *offset += 1;
    right --;

    // next can fill ( or )
    subroutine(start, offset, (const char*)start[(*offset)-1], n, right, left);
}


char ** generateParenthesis(int n, int* returnSize){

	// count total_num
	int total_num;
	int up, down;
	up = down = 1;
	for (int i=0; i<n; i++) {
		up *= (2*n-i);
		down *= (n-i);
	}
	total_num = (up/down)/(n+1);
	printf("total_num = %d\n", total_num);


	*returnSize = total_num;
	char **ret = (char**)malloc(sizeof(char*)*total_num);
	

    int right = n;
    int left = n;
    int offset = 0;

    subroutine(ret, &offset, "\0", n, n/2, n/2);

	
	return NULL;
}


int main () {
	int returnSize = 0;
	char **ret;
	for (int i=1; i<=8; i++) {
		printf("n = %d ********************\n", i);
		ret = generateParenthesis(i, &returnSize);
		for (int j=0; j<returnSize; j++) {
			printf("%s\n", ret[j]);
		}
		printf("\n");
	}
}
