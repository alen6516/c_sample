#include <stdio.h>
#include "enum_test.c"


#define MACRO(input)    __function(input)
static inline const char *
__function(ERR_TYPE err_no) {
    switch (err_no) {
        case ERRNO_1:
            return "errno_1";
        case ERRNO_2:
            return "errno_2";
        case ERRNO_3:
            return "errno_3";
        case ERRNO_4:
            return "errno_4";
        case ERRNO_5:
            return "errno_5";
        default:
            printf("assert crash\n");
            return "";
    }
}


int main () {
    ERR_TYPE ret = ERRNO_2;
    char str[8];

    sprintf(str, "%s", MACRO(ret));

    printf("%s\n", str);
    


}
