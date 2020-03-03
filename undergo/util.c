#include <stdio.h>
#include <stdint.h>

int do_nothing(const char *format, ...) {
    //printf("in test\n");
    return 0;
}
#define ASSERT_WARN(con, msg) ( (!!(con)==1) ? printf("[ASSERT FAIL] %s", (msg)): do_nothing((msg)) )

#define SIZE_OF_ARR(arr) ((int)(sizeof(arr)/sizeof(arr[0])))



typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
