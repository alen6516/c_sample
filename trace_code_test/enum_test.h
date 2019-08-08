#ifndef _ENUM_H
#define _ENUM_H

typedef enum {
    ERRNO_1 = 1,
    ERRNO_2,
    ERRNO_3,
    ERRNO_4,
    ERRNO_5

} ERR_TYPE;

/*
int main () {

    ERR_TYPE ret = ERRNO_2;

    switch (ret) {
        case ERRNO_1:
            printf("%d\n", ERRNO_1);
            return 0;
        case ERRNO_2:
            printf("%d\n", ERRNO_2);
            return 0;
        case ERRNO_3:
            printf("%d\n", ERRNO_3);
            return 0;
        case ERRNO_4:
            printf("%d\n", ERRNO_4);
            return 0;
        case ERRNO_5:
            printf("%d\n", ERRNO_5);
            return 0;
        default:
            printf("unknown\n");
    }
}
*/
#endif
