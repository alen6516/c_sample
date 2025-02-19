#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef RECURSIVE

/*
Runtime: 0 ms, faster than 100.00% of C online submissions for Valid Parentheses.
Memory Usage: 5.5 MB, less than 84.13% of C online submissions for Valid Parentheses.
*/
/* a sub routine to check a sub string,
 * return length of the string if successfully matched,
 * or -1 if fail.
 * Note the 1st char of the input string is definitely an opening parenthese.
 */
int subValid(char *s)
{
    int count = 0;      // how many unfinished parentheses
    int vturn = 0;      // we expect that the next char is a closing parenthese
    int len = 0;        // the return len of is sub
    int sub_len = 0;    // return len of the next subValid
    int backof = 1;     // offset of the matching (,[,{

    while (*s != '\0') {
        switch (*s) {
            case '(':
            case '[':
            case '{':
                if (vturn == 1) {
                    sub_len = subValid(s);
                    if (sub_len == -1) {
                        return -1;
                    } else {
                        s += sub_len;
                        backof += sub_len;
                        len += sub_len;
                        continue;
                    }
                } else {
                    count ++;
                }
                break;

            case ')':
                if (count == 0) {
                    // means this subValid is finished.
                    return len;
                } else if (*(s-backof) == '(') {
                    // check the matching parenthese
                    len += 2;
                    count --;
                    if (count == 0) {
                        vturn = 0;  // all finished now, we expect ([{ again
                        backof = 1;
                    } else {
                        vturn = 1;
                        backof += 2;
                    }
                } else {
                    return -1;
                }
                break;
            case ']':
                if (count == 0) {
                    return len;
                } else if (*(s-backof) == '[') {
                    len += 2;
                    count --;
                    if (count == 0) {
                        vturn = 0;
                        backof = 1;
                    } else {
                        vturn = 1;
                        backof += 2;
                    }
                } else {
                    return -1;
                }
                break;
            case '}':
                if (count == 0) {
                    return len;
                } else if (*(s-backof) == '{') {
                    len += 2;
                    count --;
                    if (count == 0) {
                        vturn = 0;
                        backof = 1;
                    } else {
                        vturn = 1;
                        backof += 2;
                    }
                } else {
                    return -1;
                }
                break;
            default:
                return -1;
        }
        s ++;
    }
    return (count==0) ? (len) : -1;
}


bool isValid(char * s){

    int count = 0;
    int vturn = 0;
    int sub_len = 0;
    int backof = 1;

    while (*s != '\0') {
        switch (*s) {
            case '(':
            case '[':
            case '{':
                if (vturn == 1) {
                    sub_len = subValid(s);
                    if (sub_len == -1) {
                        return 0;
                    } else {
                        s += sub_len;
                        backof += sub_len;
                        continue;
                    }
                } else {
                    count ++;
                }
                break;

            case ')':
                if (count == 0) {
                    return 0;
                } else if (*(s-backof) == '(') {
                    count --;
                    if (count == 0) {
                        vturn = 0;
                        backof = 1;
                    } else {
                        vturn = 1;
                        backof += 2;
                    }
                } else {
                    return 0;
                }
                break;
            case ']':
                if (count == 0) {
                    return 0;
                } else if (*(s-backof) == '[') {
                    count --;
                    if (count == 0) {
                        vturn = 0;
                        backof = 1;
                    } else {
                        vturn = 1;
                        backof += 2;
                    }
                } else {
                    return 0;
                }
                break;
            case '}':
                if (count == 0) {
                    return 0;
                } else if (*(s-backof) == '{') {
                    count --;
                    if (count == 0) {
                        vturn = 0;
                        backof = 1;
                    } else {
                        vturn = 1;
                        backof += 2;
                    }
                } else {
                    return 0;
                }
                break;
            default:
                return 0;
        }
        s ++;
    }
    return (count == 0);
}
#else

/*
Runtime: 20 ms, faster than 12.56% of C online submissions for Valid Parentheses.
Memory Usage: 5.6 MB, less than 84.73% of C online submissions for Valid Parentheses.
*/

/* Set the matched parenthese to another char,
 * so when we can skip it in the next scanning.
 */
#define CLEAR_CHAR '*'
bool isValid(char * s){

    int i;
    char *start = s;
    int count = 0;  // how many matched parentheses
    int found;
    char c = '\0';  // the target parenthese

    while (*s != '\0') {
        switch (*s) {
            case '(':
            case '[':
            case '{':
                count ++;
                break;

            case ')':
                if (c == '\0') {
                    c = '(';
                }

            case ']':
                if (c == '\0') {
                    c = '[';
                }

            case '}':
                if (c == '\0') {
                    c = '{';
                }

                found = 0;
                for (i=1; i<=(s-start); i++) {
                    // scanning
                    if (*(s-i) == CLEAR_CHAR) {
                        continue;
                    } else if (*(s-i) == c) {
                        *(s-i) = CLEAR_CHAR;
                        *s = CLEAR_CHAR;
                        found = 1;
                        count --;
                        break;
                    } else {
                        return 0;
                    }
                }
                if (!found) {
                    return 0;
                } else {
                    // reset
                    found = 0;
                    c = '\0';
                }
                break;
            default:
                return 0;
        }
        s ++;
    }

    return (count == 0);
}
#endif

int main () {

    char arr[] = {'(', ')', '[', ']', '{', '}'};
    for (int i=0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        printf("%c, %d\n", arr[i], arr[i]);
    }

    //char s[]  = "{()}[()]";
    //char s[] = "[[{}([]){}]]";
    //char s[] = "[{}()}";
    //char s[] = "(";
    //char s[] = "}";
    char s[] = "[[{}([]{}){}]]";

    printf("%s\n", s);
    printf("%d\n", isValid(s));
}
