#include <stdio.h>
#include <stdlib.h>

// return Nth fibo
int fib(int n)
{
    if (n <= 0) return 0;
    else if (n == 1) return 1;
    return fib(n-1) + fib(n-2);
}

void all_fib(int n)
{
    for (int i=0; i<=n; i++) {
        printf("%d ", fib(i));
    }
}

int main(int argc, char *argv[])
{
    int input;

    if (argc > 1) 
        input = (int) strtol(argv[1], NULL, 10);
    else
        input = 10;

    printf("%d\n", input);

    printf("all fib of %d: ", input);
    all_fib(input);
    printf("\nfib: %d\n", fib(input));
}
