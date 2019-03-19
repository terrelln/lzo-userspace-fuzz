#include <stddef.h>
#include <stdint.h>

#include "kernel.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define noinline __attribute__((noinline))
#define expect(b, t) (__builtin_expect((b), (t)))
#define likely(b) expect((b), 1)
#define unlikely(b) expect((b), 0)

#undef __LITTLE_ENDIAN
#undef __BIG_ENDIAN
#define __LITTLE_ENDIAN
#define BUILD_BUG_ON(x) static_assert(!(x), "")
