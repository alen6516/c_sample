#include <stdio.h>
#include <stdlib.h>

/*
 * integer to string
 */

char *itoa(int num) {
	int len;
	int tmp = num;
	for(len = 0; tmp != 0; len++, tmp/=10);
	char *res = (char*)malloc(sizeof(char)*(len+1));
	for(int i=1; i<len+1; i++) {
		*(res+i) = num%10+'0';
		num /= 10;
	}
	*res = 0;

	int t;
	for(int i=0; i<(len+1)/2; i++) {
		t = *(res+i);
		*(res+i) = *(res+len-i);
		*(res+len-i) = t;
	}

	return res;
}

int main() {
	printf("%s\n", itoa(12345));
	
}
