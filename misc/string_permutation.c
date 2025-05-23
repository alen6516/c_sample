#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* given "abc" and print all permutation:
 * abc, acb, bac, bca, cab, cba
 */


int len;    // length of the input string

int permutation(char *str, char *prefix)
{
    int prefix_len = strlen(prefix);

    if (prefix_len == len)
        printf("%s\n", prefix);
    else {
        char curr;
        for (int i=0; i < len; i++) {
            if (str[i] == '\0') continue;   // skip if char is musked
            curr = str[i];
            prefix[prefix_len] = curr;
            str[i] = '\0';                  // musk char
            permutation(str, prefix);

            // permute done, recover curr
            prefix[prefix_len] = '\0';
            str[i] = curr;
        }
    }
}

int main(int argc, char *argv[])
{
    char str[10] = {0};
    if (argc > 1) 
        strncpy(str, argv[1], 9);
    else
        strncpy(str, "abc", 3);

    len = strlen(str);

    printf("%s, %d\n", str, len);

    char *prefix = (char *)malloc(len+1);
    memset(prefix, 0, len+1);
    permutation(str, prefix);
}
