
#include <stdio.h>
#include <string.h>
int main() {

	// 不能用 = 來 assign 一個 array
	str = "string";		// error: assignment to expression with array type
	arr = {1, 2, 3}; 	// error: expected expression before ’ token
	str1 = str2; 		// error: assignment to expression with array type


	// 可以初始化 (在 declaration 時，這裡的 = 不是 assign)
	char s[10] = "string"; 	// 合法


	// 使用 == 來比較兩 array 是合法的，但不會產生預期結果 (兩者被視為 pointer 來比較，因為兩者 address 不同，所以不會相等)
	if ( str1 == str2 ) ... // no error


    // 未初始化的 array，裡面每個 char 的值不定，print 不出來，可能是 '\0' 也可能不是
    char s[5];
    printf("%s\n", s);  // 空的
    for (int i=0; i<5; i++) printf("%c", s[i] == '\0' ?'y':'n');    // nnnyy
    printf("");
    for (int i=0; i<5; i++) printf("%c", s[i] == ' ' ?'y':'n');     // nnnnn
    printf("");


	// size of int array
	int arr[] = {1, 2, 3};
	printf("%d\n", (int)sizeof(arr));	// 3 個 int => 12

	// size of char array
	char str[] = {'1', '2', '3'};
	printf("%d\n", (int)sizeof(str));	// 3 個 char => 3

	// size of string
	char str[] = "123";
	printf("%d\n", (int)sizeof(str));	// 結尾有一個 '\0' => 4

	char *str = "123";
	printf("%d\n", (int)sizeof(str)); 	// str 是 pointer!! => 8


	// int array shift
	int arr[] = {1, 2, 3};
	printf("%d\n", (arr+1)[1]);			// 出現 + 時，arr 視為 pointer ，arr+1 指向 2，而 (arr+1)[] 則又視為陣列 {2, 3} ，該陣列第 1 項 => 3
	printf("%d\n", (int)sizeof(arr+0));	// 出現 + 時，arr 視為 pointer => 8

	// char arr shift
	char *str = "abc";
	printf("%c\n", (str+1)[1]); 		// c
	printf("%d\n", sizeof(str+1));		// pointer => 8
	printf("%d\n", sizeof(str));		// pointer => 8


}
