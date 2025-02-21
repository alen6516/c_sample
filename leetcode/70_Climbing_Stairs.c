#include <stdio.h>
#include <stdlib.h>

// permutation(x, y)
unsigned long p_x_y(int x, int y)
{
    if (x == 0 || y == 0) { printf("p(%d, %d) = 1\n", x, y); return 1;}
    else if (x == 1 || y == 1) { printf("p(%d, %d) = %d\n", x, y, x+y); return x+y;}

    int i = (x < y) ? x : y;
    unsigned long r1, r2;
    r1 = r2 = 1;
    printf("p(%d, %d) = ", x, y);

    x = x+y;
    y = i;
    printf("%dx...x%d/%dx...x%d = ", x, x-i+1, y, y-i+1);
    for (; i>0; i--) {
        r1 = r1*(x--);
        r2 = r2*(y--);
    }
    printf("%lu\n", r1/r2);
    return r1/r2;
}

int climbStairs(int n)
{
    int x = n >> 1;
    int y = (n & 1);

    unsigned long r = 0;
    while (x >= 0) {
        r += p_x_y(x, y);
        //printf("(%02d, %02d) = %ld\n", x, y, r);
        x = x-1;    // 1x = 2y
        y = y+2;
    }
    return (int)r;
}


// recursive method, correct but slow
// using arr to cache answer and improve performance
// Runtime 0 ms Beats 100.00%
// Memory 7.81 MB Beats 27.54%
int _climbStairs(int n) {
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
    a1 = arr[n-2] ? arr[n-2] : _climbStairs(n-1);
    a2 = arr[n-3] ? arr[n-3] : _climbStairs(n-2);
    arr[n-1] = a1+a2;
    return arr[n-1];
}

int main(int argc, char *argv[])
{
    int n=3;
    if (argc > 1)
        n = strtol(argv[1], NULL, 10);
    printf("n=%d, s=%d\n", n, climbStairs(n));
    printf("n=%d, s=%d\n", n, _climbStairs(n));
}
