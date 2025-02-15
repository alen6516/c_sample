#include <stdio.h>
#include <stdlib.h>

// permutation(x, y)
int p_x_y(int x, int y)
{
    if (x & y == 0) return 1;
    else if (x == 1 || y == 1) return x*y;

    int i = (x < y) ? y : x;
    int r1, r2;
    r1 = r2 = 1;

    x = x+y;
    y = i;
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
        r += p_x_y(x, y);
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
