#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int _strStr(char * haystack, char * needle){
    if (haystack[0] == '\0') {
        if (needle[0] == '\0') {
            return 0;
        } else {
            return -1;
        }
    } else if (needle[0] == '\0') {
        return 0;
    }


    int pos = 0;
    int adv = 0;
    int i = 0;

    while(haystack[pos+i] != '\0') {
        if (haystack[pos+i] == needle[0] && i!=0 && adv==0) {
            adv = i;
        }
        if (haystack[pos+i] != needle[i]) {
            if (adv) {
                pos += adv;
            } else {
                pos += (i+1);
            }
            adv = 0;
            i = 0;
        } else { 
            if (needle[i+1] == '\0') {
                return pos;
            } else if (haystack[pos+i+1] == '\0') {
                return -1;
            } else {
                i++;
            }
        }
    }
    return -1;
}

int strStr(char *haystack, char *needle) {
    if (haystack[0] == '\0') {
        if (needle[0] == '\0') {
            return 0;
        } else {
            return -1;
        }
    } else if (needle[0] == '\0') {
        return 0;
    }

    int len1, len2;
    for (len1=0; haystack[len1] != '\0'; len1++);
    for (len2=0; needle[len2] != '\0'; len2++);
    
    printf("%d, %d\n", len1, len2);

    if (len1 < len2) return -1;

    int i=0;
    int pos = 0;
    int adv = 0;
    while (pos+len2 <= len1) {
        if (haystack[pos+i] == needle[i] &&
            haystack[pos+len2-1-i] == needle[len2-1-i]) {

            if (pos+i == pos+len2-1-i) {
                return pos;
            }
            if (haystack[pos+i] == needle[0] && i!=0 && adv==0) {
                adv = i;
            }

        } else {
            pos += adv;
            i = 0;
            adv = 0;
        }
    }
    return -1;
}

int main ()
{
    srand(time(NULL));
    int len = (rand() % 10) + 5;
    char *str = (char*)malloc(sizeof(len+1));

    // gen random str
    for (int i=0; i<len+1; i++) {
        str[i] = 'a'+(rand() % 26);
    }
    str[len] = '\0';
    printf("%s\n", str);

    // gen random key
    int key_pos = rand() % len;
    int key_len = (rand() % 3)+2;
    char key[5];
    for (int i=0; i<key_len; i++) {
        if (key_pos+i > len-1) {
            key[i] = '\0';
            break;
        }
        key[i] = str[key_pos+i];
    }
    key[key_len] = '\0';
    printf("key = \"%s\"\n", key);

    int ret = strStr(str, key);
    printf("pos = %d\n", ret);
}
