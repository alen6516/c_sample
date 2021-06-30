/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	

	// render string
	int curr_num = 0;
	const char pre[] = "((((";
	ret[curr_num] = (char*) malloc (n+1);
	strncpy(ret[curr_num], pre, strlen(pre));
	strncpy(ret[curr_num]+4, "))))", 4);
	printf("%s, len = %d\n", ret[curr_num], (int)strlen(ret[curr_num]));


	ret[0] = (char*)malloc(2*n+1);
	memset(ret[0], '(', 2*n);
	ret[0][2*n] = '\0';
	int count = 0;

	divide()
	
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
