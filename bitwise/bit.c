#include <stdio.h>

unsigned map;

// first bit is bit 0
void set_bit(int bit)
{
    printf("before set      : 0x%x\n", map);
    map = map | (1 << bit);
    printf("after set bit %2d: 0x%x\n", bit, map);
}
void clear_bit(int bit)
{
    printf("before clear      : 0x%x\n", map);
    map = map & ~(1 << bit);
    printf("after clear bit %2d: 0x%x\n", bit, map);
}

void test_bit(int bit)
{
    printf("test bit %d in 0x%x\n", bit, map);
    printf("bit is %sset\n", ((map >> bit) & 0x1) ? "": "un");
}

void toggle_bit(int bit);

int main()
{
    set_bit(4);
    test_bit(4);
    clear_bit(4);
    test_bit(4);
}
