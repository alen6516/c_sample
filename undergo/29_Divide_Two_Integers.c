#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IS_SAME_SIGN(a,b) (((a)^(b)) >= 0)

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

    
    int ret = 0;

    if (IS_SAME_SIGN(dividend, divisor)) {
        while (IS_SAME_SIGN(dividend, divisor)) {
            dividend -= divisor;
            ret ++;
        }
        ret --;
    } else {
        while (!IS_SAME_SIGN(dividend, divisor)) {
            dividend += divisor;
            ret --;
        }
        ret ++;
    }
    return ret;
}

int main ()
{
    srand(time(NULL));

    int dividend, divisor;
    dividend = rand() % 100;
    divisor = rand() % 50;

    if ((rand() % 3)) {
        dividend = 0-dividend;
    }
    if ((rand() % 3)) {
        divisor = 0-divisor;
    }

    printf("dividend = %d\n divisor = %d\n", dividend, divisor);
    printf("expect   = %d\n", dividend/divisor);
    printf("result   = %d\n", divide(dividend, divisor));
}
