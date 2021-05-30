/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

char ** generateParenthesis(int n, int* returnSize){
	
	char *p;
	p = (char*) malloc(n*2);
	p[0] = '(';
	
	
}

int main () {
	int returnSize = 0;
	char **ret;
	for (int i=1; i<=8; i++) {
		ret = generateParenthesis(i, &returnSize);
		printf("n = %d ********************\n", i);
		for (int j=0; j<returnSize; j++) {
			printf("%s\n", ret[j]);
		}
		printf("\n");
	}
}
