#include <stdio.h>
#include <stdlib.h>

// permutation(x, y)
int p_x_y(int x, int y)
{
    if ((x & y) == 0) return 1;
    else if (x == 1 || y == 1) return x*y;

    int i = (x < y) ? x : y;
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
    while (x >= 0) {
        r += p_x_y(x, y);
        x = x-1;    // 1x = 2y
        y = y+2;
    }
    return r;
}


#ifdef alan
// recursive method, correct but slow
// using arr to cache answer and improve performance
// Runtime 0 ms Beats 100.00%
// Memory 7.81 MB Beats 27.54%
int climbStairs(int n) {
    static int arr[45] = {0};

    if (n==1) {
        if (!arr[0])
            arr[0] = 1;
        return arr[0];
    } else if (n==2) {
        if (!arr[1])
            arr[1] = 2;
        return arr[1];
    } else if (arr[n-1])
        return arr[n-1];

    int a1, a2;
    a1 = arr[n-2] ? arr[n-2] : climbStairs(n-1);
    a2 = arr[n-3] ? arr[n-3] : climbStairs(n-2);
    arr[n-1] = a1+a2;
    return arr[n-1];
}
#endif

int main(int argc, char *argv[])
{
    int n=3;
    if (argc > 1)
        n = strtol(argv[1], NULL, 10);
    printf("n=%d, s=%d\n", n, climbStairs(n));
}
