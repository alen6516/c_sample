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

#define SWAP(a, b) ({   \
    if ((a) != (b)) {   \
        a = a^b;        \
        b = a^b;        \
        a = a^b;        \
    }                   \
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


clock_t __start, __end;
#define CLOCK_START() ({ __start = clock(); })
#define CLOCK_END()   ({ __end = clock(); })
#define CLOCK_DIFF()  (__end - __start)
#endif
