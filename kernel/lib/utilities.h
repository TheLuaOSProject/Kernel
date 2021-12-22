/**
 * @file    utilities.h
 * @author  Amrit Bhogal (@Frityet)
 * @brief   Commonly used utilities that I was to lazy to put in the proper files
 * @version 1.0
 * @date    2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */

#ifndef LUAOS_UTILITIES
#define LUAOS_UTILITIES

#include "types.h"

static inline uint64_t round_division(uint64_t a, uint64_t b)
{
    return (a + (b - 1) / b);
}

// #define CEIL_DIV(num, div) ((div + num - 1) / div) 

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
extern void CRASH(void);

/**
 * Divides by zero (doing in C results in the UD2 instruction being generated)
 */
extern void DIV_BY_ZERO(void);

/**
 * Executes the debug interrupt (0x72)
 */
extern void DEBUG_INTERRUPT(void);

/**
 * Executes the breakpoint interrupt
 */
extern void BREAKPOINT(void);

extern void HALT(void);

#endif //LUAOS_UTILITIES
