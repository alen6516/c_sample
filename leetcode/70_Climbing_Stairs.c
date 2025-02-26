#include <stdio.h>
#include <stdlib.h>

#ifdef permutation
//Runtime 0 ms Beats 100.00%
//Complexity Memory 7.70 MB Beats 94.71%

// permutation(x, y)
unsigned long p_x_y(int x, int y)
{
    if (x == 0 || y == 0) return 1;
    else if (x == 1 || y == 1) return x+y;

    int num = (x < y) ? x : y;
    unsigned long r = 1;

    /*      x+y    tx1 * tx2 * ...
     *  r = --- = -----------------
     *       y     ty1 * ty2 * ...
     */

    unsigned int map = 0;   // bitmap to check if ty can be divided
    int tx;
    for (int i=0; i<num; i++) {
        tx = x+y-i;
        for (int ty=num; ty>1; ty--) {
            if (1 == ((map >> ty) & 1))  // this ty is used
                continue;
            else if ((tx % ty) == 0) {  // this ty can be used
                tx = tx/ty;
                map = map | (0x1 << ty);   // mark this ty
                break;
            }
        }
        r *= tx;
    }

    // still need to check if all ty are divided
    for (int ty=num; ty>1; ty--) {
        if (0 == ((map >> ty) & 0x1))  // this ty is not used
            r /= ty;
    }

    //printf("%lu\n", r);
    return r;
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

#else
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
    a1 = arr[n-2] ? arr[n-2] : _climbStairs(n-1);
    a2 = arr[n-3] ? arr[n-3] : _climbStairs(n-2);
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
    printf("n=%d, s=%d\n", n, _climbStairs(n));
}
