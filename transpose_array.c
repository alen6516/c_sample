#include <stdio.h>

int main() {

	// 不能以 arr[][] 宣告，必須指明除了第一維之外的維度大小	
	int arr[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
	
	int i = sizeof(arr)/sizeof(arr[0]);
	int j = sizeof(arr[0])/sizeof(arr[0][0]);

	/**printf("%d %d\n", i, j);*/

	int result[j][i];

	// assign
	for(int a=0; a<j; a++)
		for(int b=0; b<i; b++)
			result[a][b] = arr[b][a];

	// print
	for(int a=0; a<j; a++) {
		for(int b=0; b<i; b++)
			printf("%d ", result[a][b]);
		printf(" \n");
	}
}
