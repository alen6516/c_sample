#include <stdio.h>

int atoi(char *s) {
	
	int sum = 0;
	for (int i=0; s[i] != 0; i++) {
		sum = sum*10 + s[i]-'0';
	}
	return sum;


}

int main() {
	char *s = "12345";
	int ret = atoi(s);
	printf("%d\n", ret);
}
