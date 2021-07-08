/*
Runtime: 4 ms, faster than 66.46% of C online submissions for Generate Parentheses.
Memory Usage: 6.7 MB, less than 44.51% of C online submissions for Generate Parentheses.
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int malloc_times[8] = {0};

// start: first char*'s addr
// right, left: num of the remaining ( or )
// offset: the num of char we have
void subroutine(char **start, int *offset, const char* pattern, const int n, int right, int left)
{
    // malloc this
    char *this = (char*) malloc(n+1);
    malloc_times[(n/2)-1] ++;

    start[*offset] = this;
    if (right > left) {
        strncpy(this, pattern, n-right-left);
        this[n-right-left] = ')';
        right --;
    }

    while (left > 0) {
        // if can fill right, then need to call itself again to malloc, copy and fill ')'
        if (right > left) {
            (*offset) += 1;
            subroutine(start, offset, this, n, right, left);
        }

        // if can fill left, then just fill it in curr string
        if (left > 0) {
            this[n-right-left] = '(';
            left --;
        }
    }

    // fill all remaining ')'
    memset(&this[n-right-left], ')', right);
    this[n] = '\0';
}

// n is pair num
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
	
    int offset = 0;

    subroutine(ret, &offset, "\0", (const int)2*n, n, n);
    printf("malloc_times = %d\n", malloc_times[n-1]);

	return ret;
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
