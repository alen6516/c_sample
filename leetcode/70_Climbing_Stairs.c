#include <stdio.h>
#include <stdlib.h>

int c_x_y(int x, int y)
{
    if (x & y == 0) return 1;
    else if (x == 1 || y == 1) return x*y;
    else if (y>x) {
        x = x^y;
        y = x^y;
        x = x^y;
    }

    int r1, r2;
    r1 = r2 = 1;
    int i = (x-y < y) ? (x-y) : y;
    for (; i>0; i--) {
        r1 = r1*(x--);
        r2 = r2*(y--);
    }
    return r1/r2;
}

int climbStairs(int n)
{
    int x = n >> 1;
    int y = (n & 1);

    int r = 0;
    while(x >= 0) {
        r += c_x_y(x, y);
        x = x-1;
        y = y+2;
    }
    return r;
}



// recursive method, correct but slow
int climbStairs(int n) {
    if (n==1) return 1;
    else if (n==2) return 2;
    else return climbStairs(n-2)+climbStairs(n-1);
}

int main(int argc, char *argv[])
{
    int n=3;
    if (argc > 1)
        n = strtol(argv[1], NULL, 10);
    printf("n=%d, s=%d\n", n, climbStairs(n));
}
