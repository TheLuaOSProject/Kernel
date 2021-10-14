//
// Created by Frityet on 2021-09-16.
//

#ifndef LUAOS_UTILITIES
#define LUAOS_UTILITIES
#include "types.h"

#define ROUND_UP(A, B) ({                                   \
        typeof(A) _a_ROUND_UP_ = A;                         \
        typeof(B) _b_ROUND_UP_ = B;                         \
        (_a_ROUND_UP_ + (_b_ROUND_UP_ - 1)) / _b_ROUND_UP_; \
})

#define CLEAR_BIT(BITMAP, BIT) ({                   \
        BITMAP[BIT / 8] |= (1 << (7 - BIT % 8));    \
})

void memset(void        *pointer,
            uintmax_t   value,
            uintmax_t   bytes);

/**
 * Copies memory from a source to a destination
 * @param src Source memory
 * @param dest Destination of the memory
 * @param byte_count Number of bytes to copy
 */
void memcpy(const int8_t    *src,
            int8_t          *dest,
            int             byte_count);

/**
 * Instantly crashes the machine by calling the UD2 instruction
 */
extern void CRASH();

/**
 * Divides by zero (doing in C results in the UD2 instruction being generated)
 */
extern void DIV_BY_ZERO();

/**
 * Executes the debug interrupt (0x72)
 */
extern void DEBUG_INTERRUPT();

/**
 * Executes the breakpoint interrupt
 */
extern void BREAKPOINT();

#endif //LUAOS_UTILITIES
