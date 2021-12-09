//
// Created by Frityet on 2021-10-14.
//

#ifndef LUAOS_BITMAP
#define LUAOS_BITMAP

#include "types.h"

static inline void clear_bit(uint8_t *bitmap, uintptr_t bit)
{
    bitmap[bit / 8] |= (1 << (7 - bit % 8));
}

static inline bool test_bit(const uint8_t *bitmap, uintptr_t bit)
{
    if (bitmap[bit / 8] & (1 << (7 - bit % 8))) return false;
    else return true;
}

static inline void set_bit(uint8_t *bitmap, uintptr_t bit)
{
    bitmap[bit / 8] |= (1 << (7 - bit % 8));
}


#endif //LUAOS_BITMAP
