/***
 File Name: c.c
 Author: alen6516
 Created Time: 2019-04-16
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
	
	// # ========== 複製 ==========
	// char *strcpy(char *s1, const char *s2)
	// char *strncpy(char *s1, const char *s2, size_t n)

	// # ========== 串接 ==========
	// char *strcat(char *s1, const char *s2)
	// char *strncat(char *s1, const char *s2, size_t n)

	// # ========== 比較 ==========
	// int char strcmp( const char *s1, const char *s2)
	// int char strncmp( const char *s1, const char *s2, size_t n)

	// 計算長度
	// size_t strlen(const char *s)
	
	// # ========== 搜尋 ==========
	// 回傳在字串 s 中，字元 c 第一次出現位置的指標
	// char *strchr(const char *s, int c)

	// 計算經過幾個字元會在字串 s1 中遇到屬於 s2 中的字元
	// size_t strcspn(const char *s1, const char *s2)

	// 計算經過幾個字元會在字串 s1 中遇到不屬於 s2 中的字元
	// size_t strspn(const char *s1, const char *s2)

    // 回傳在字串 s2 中的任何字元在 s1 第一次出現位置的指標
	// char *strpbrk(const char *s1, const char *s2)
	
	// 回傳在字串 s 中，字元 c 最後一次出現位置的指標
	// char *strrchr(const char *s, int c)

    // 回傳在字串 s2 在 s1 第一次出現位置的指標
	// char *strstr(const char *s1, const char *s2)
	
	// 以字串 s2 的內容切割 s1
	// char *strtok(char *s1, const char *s2)

	// # ========== memory ==========
	// 從 s2 所指向的資料複製 n 個字元到 s1
	// void *memcpy(void *s1, const void *s2, size_t n)

 	// 從 s2 所指向的資料複製 n 個字元到 s1
	// void *memmove(void *s1, const void *s2, size_t n)

   	// 比較 s1 與 s2 前 n 個字元的資料
	// int memcmp(const void *s1, const void *s2, size_t n)

 	// 找出字元 c 在 s 前 n 個字元第一次出現的位置
	// void *memchr(const void *s, int c, size_t n)

 	// 將 s 中前 n 個字元全部設定為 c
	// void *memset(void *s, int c, size_t n)
}
