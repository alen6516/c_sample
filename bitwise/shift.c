#include <stdio.h>
#include <time.h>

unsigned long check1(unsigned long input)
{
    return input * 3;
}

unsigned long check2(unsigned long input)
{
    return (input << 2) - (input);
}

#define NUM 10000000

int main()
{
    unsigned long a = 1L;
    clock_t start, end;
    double total;

    start = clock();
    for (int i=0; i<NUM; i++) {
        check1(a);
    }
    end = clock();
    total = (double)(end-start)/CLOCKS_PER_SEC;
    printf("%f sec\n", total);

    start = clock();
    for (int i=0; i<NUM; i++) {
        check2(a);
    }
    end = clock();
    total = (double)(end-start)/CLOCKS_PER_SEC;
    printf("%f sec\n", total);
}
