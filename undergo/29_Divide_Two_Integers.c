#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int divide(int dividend, int divisor)
{
    if (dividend == 0) {
        return 0;
    }
    if (divisor == 1) {
        return dividend;
    } else if (divisor == -1) {
        return (0-dividend);
    }

    
    int ret = 0;
    while (dividend > divisor) {
        dividend -= divisor;
        ret ++;
    }
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

    printf("dividend = %d, divisor = %d\n", dividend, divisor);

}
