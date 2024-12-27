#include <stdio.h>
#include <stdlib.h>

// given an input, print all power-of-2 value less than the input
int _power_of_2(int input)
{
    int ret;
    input = input >> 1;
    if (input == 0) {
        ret = 1;
    } else {
        ret = 2*_power_of_2(input);
    }
    printf("%d ", ret);
    return ret;
}

int power_of_2(int input)
{
    int ret = 1;
    int count = 0;
    while (input != 0) {
        input = input >> 1;
        count ++;
    }
    while (count --) {
        printf("%d ", ret);
        ret = ret << 1;
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

    power_of_2(input);
    printf("\n");
}
