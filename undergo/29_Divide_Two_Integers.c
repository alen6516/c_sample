#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IS_SAME_SIGN(a,b) (!(a) || !(b) || ((a)^(b)) >= 0)

int divide(int dividend, int divisor)
{
    if (dividend == 0) {
        return 0;
    }
    if (divisor == 1) {
        return dividend;
    } else if (divisor == -1) {
        return (dividend == (1<<31)) ? (~divisor) : (~divisor)+1 ;
    }
#ifdef new
    if (dividend < 0) {
        dividend = (~dividend)+1;
    }
    if (divisor) {
        divisor = (~divisor)+1;
    }

    int curr_bit = 0;
    while ((dividend >> curr_bit) > divisor ) {
        curr_bit ++;
    }
    curr_bit -= 1;

    int ret, remain;
    ret = remaina = 0;

#else

    
    int ret = 0;
    int ori_dividend = dividend;
    int revert = 0;

    if (!IS_SAME_SIGN(dividend, divisor)) {
        divisor = (~divisor)+1;
        revert = 1;
    }

    while (IS_SAME_SIGN(dividend, ori_dividend)) {
        dividend -= divisor;
        ret ++;
    }
    ret --;
    /*
    if (IS_SAME_SIGN(dividend, ori_dividend)) {
        while (IS_SAME_SIGN(dividend, divisor)) {
            dividend -= divisor;
            ret ++;
        }
        ret --;
    } else {
        while (!IS_SAME_SIGN(dividend, ori_dividend)) {
            //printf("%d %d, not same sign\n", dividend, divisor);
            dividend += divisor;
            ret --;
        }
        ret ++;
    }
    */
    return (revert) ? (~ret+1) : ret;
#endif
}

int main (int argc, char *argv[])
{
    srand(time(NULL));

    int dividend, divisor;
    if (argc < 3) {
        dividend = rand() % 100;
        divisor = rand() % 50;

        if ((rand() % 3)) {
            dividend = 0-dividend;
        }
        if ((rand() % 3)) {
            divisor = 0-divisor;
        }
    } else {
        dividend = strtol(argv[1], NULL, 10);
        divisor = strtol(argv[2], NULL, 10);
    }

    printf("dividend = %d\n divisor = %d\n", dividend, divisor);
    printf("expect   = %d\n", dividend/divisor);
    printf("result   = %d\n", divide(dividend, divisor));
}
