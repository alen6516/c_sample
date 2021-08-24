#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int strStr(char * haystack, char * needle){
    int pos = 0;
    int adv = 0;
    int i = 0;

    while(1) {
        if (haystack[pos+i] == needle[0] && i!=0 && adv==0) {
            adv = i;
        }
        if (haystack[pos+i] != needle[i]) {
            if (adv) {
                pos += adv;
            } else {
                pos += 1;
            }
            adv = 0;
            i = 0;
        } else if (needle[i+1] == '\0') {
            return pos;
        } else {
            i++;
        }
    }
    return -1;
}

int main ()
{
    srand(time(NULL));
    int len = (rand() % 10) + 5;
    char *str = (char*)malloc(sizeof(len+1));

    for (int i=0; i<len; i++) {
        str[i] = 'a'+(rand() % 26);
    }
    str[len] = '\0';
    printf("%s\n", str);

    int key_pos = rand() % len;
    int key_len = rand() % 6;
    char key[6];
    for (int i=0; i<key_len; i++) {
        key[i] = str[key_pos+i]
        if (key_pos+i == len-1) {
           break;
        }
    }

    int ret = strStr(str, key)

    printf("key = \"%s\"\n", key);
    printf("pos = %d\n", ret);
}
