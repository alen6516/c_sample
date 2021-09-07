#include <stdio.h>

#define BIT_WORD(nr)            ((nr) / BITS_PER_LONG)

#ifdef CONFIG_64BIT
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif /* CONFIG_64BIT */

static inline int test_bit(int nr, const volatile unsigned long *addr)
{
    return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}
/*
static inline int test_and_set_bit(unsigned int nr, volatile unsigned long *p)
{
        long old;
        unsigned long mask = BIT_MASK(nr);

        p += BIT_WORD(nr);
        if (READ_ONCE(*p) & mask)
                return 1;

        old = atomic_long_fetch_or(mask, (atomic_long_t *)p);
        return !!(old & mask);
}
*/
int main() {
    unsigned long map = 0x0;
	int ret = 0;
	ret = test_bit(5, &map);
    printf("%d\n", ret);

    map |= (1<<6);
	ret = test_bit(5, &map);
    printf("%d\n", ret);
}
