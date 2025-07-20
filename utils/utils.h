#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

//typedef uint8_t bool_t;     // just use bool, true, false from stdbool.h
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// swap for integer and ptr, not working for float
#define SWAP(x, y) ({   \
    if ((x) != (y)) {   \
        x = (typeof(x)) ((uintptr_t)x ^ (uintptr_t)y);  \
        y = (typeof(x)) ((uintptr_t)x ^ (uintptr_t)y);  \
        x = (typeof(x)) ((uintptr_t)x ^ (uintptr_t)y);  \
    }                                                   \
})

#ifdef DEBUG
#define DEBUG(...) ({                                   \
        printf("[DEBUG] %s: ", __func__);               \
        printf(__VA_ARGS__);                            \
})
#else
#define DEBUG(...)
#endif

/* throw an error at compile time */
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

/* when condition occur, we must exit, but we don't want to */
#define ASSERT_WARN(con, msg) do {                      \
    if (!!(con)==0) {                                   \
        printf("[ASSERT WARN] %s", (msg))               \
    }                                                   \
} while(0)

/* when condition occur, we must exit immidiately */
#define ASSERT_EXIT(con, msg) do {                      \
    if (!!(con)==0) {                                   \
        printf("[ASSERT EXIT] %s\n", msg);              \
        exit(-1);                                       \
    }                                                   \
} while(0)


extern clock_t __start, __end;
#define CLOCK_START() ({ __start = clock(); })
#define CLOCK_END()   ({ __end = clock(); })
#define CLOCK_DIFF()  (__end - __start)
#define CLOCK_DIFF_SEC() ((float)(__end - __start)/CLOCKS_PER_SEC)

/* print byte in binary */
#define B2b_PATTERN "0b%c%c%c%c%c%c%c%c"
#define B2b(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

/**
 * example:
 * printf("Leading ext " B2b_pattern, B2b(byte));
 *
 * for 2-byte types:
 * printf("m: "B2b_pattern" "B2b_pattern"\n", B2b(m>>8), B2b(m));
 */

#endif
