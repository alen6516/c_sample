#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// replace space in a string with '%20'
int main()
{
    char *str = "Mr John Smith";    // return "Mr%20John%20Smith"
    int len = strlen(str);

    char *ret;
    int ret_len = len+2*2+1;

    printf("%s\n", str);
    printf("%d\n", ret_len);

    ret = (char*) malloc(ret_len);
    ret[ret_len-1] = '\0';

    int i = ret_len-2;
    int j = len -1;

    while (j >= 0) {
        if (str[j]==' ') {
            ret[i--] = '0';
            ret[i--] = '2';
            ret[i--] = '%';
        } else {
            ret[i--] = str[j];
        }
        j--;
    }

    printf("%s\n", ret);
}
