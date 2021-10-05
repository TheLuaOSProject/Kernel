//
// Created by Frityet on 2021-09-16.
//

#ifndef LUAOS_UTILITIES
#define LUAOS_UTILITIES
#include "types.h"

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


#endif //LUAOS_UTILITIES
