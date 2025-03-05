#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//#ifdef stack
    

//#endif


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
int subValid(char *s, bool in_sub)
{
    int count = 0;      // how many unfinished parentheses
    int vturn = 0;      // we expect that the next char is a closing parenthese, but it isn't
    int len = 0;        // the return len of current sub
    int sub_len = 0;    // return len of the next subValid
    int backof = 1;     // offset of the corresponding (,[,{ of a ),],}
    char this;

    while (*s != '\0') {
        switch (*s) {
            case '(':
            case '[':
            case '{':
                if (vturn == 1) {   // we expect )]}, but see ([{
                    sub_len = subValid(s, 1);
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
                this = '(';
                goto check;
            case ']':
                this = '[';
                goto check;
            case '}':
                this = '{';
check:
                if (count == 0) {   // if count == 0, it should be at the end of a sub, or wrong
                    return (in_sub) ? len: -1;
                } else if (*(s-backof) == this) {
                    // check the matching parenthese
                    len += 2;
                    count --;
                    if (count == 0) {
                        vturn = 0;  // all finished now, we expect ([{ again
                        backof = 1;
                        //return len;
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

bool isValid(char * s)
{
    return (subValid(s, 0) != -1);
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

    //char arr[] = {'(', ')', '[', ']', '{', '}'};
    //for (int i=0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    //    printf("%c, %d\n", arr[i], arr[i]);
    //}

    char s1[]  = "{()}[()]";
    printf("%s\n", s1);
    printf("%d\n", isValid(s1));

    char s2[] = "[[{}([]){}]]";
    printf("%s\n", s2);
    printf("%d\n", isValid(s2));

    char s3[] = "[{}()}";
    printf("%s\n", s3);
    printf("%d\n", isValid(s3));

    char s4[] = "(";
    printf("%s\n", s4);
    printf("%d\n", isValid(s4));

    char s5[] = "}";
    printf("%s\n", s5);
    printf("%d\n", isValid(s5));

    char s6[] = "[[{}([]{}){}]]";
    printf("%s\n", s6);
    printf("%d\n", isValid(s6));

    char s7[] = "()}";
    printf("%s\n", s7);
    printf("%d\n", isValid(s7));
}
