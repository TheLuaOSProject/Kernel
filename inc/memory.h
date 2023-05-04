/**
 * Copyright (C) 2023 Amrit Bhogal
 *
 * This file is part of LuaOS.
 *
 * LuaOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LuaOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LuaOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <common.h>

NONNULL_BEGIN

static void *memory_copy(void *dst, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
        ((byte *)dst)[i] = ((byte *)src)[i];

    return dst;
}

static void *memory_set(void *dst, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        ((byte *)dst)[i] = c;

    return dst;
}

static int memory_compare(const void *b1, const void *b2, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (((byte *)b1)[i] < ((byte *)b2)[i]) return -1;
        if (((byte *)b1)[i] > ((byte *)b2)[i]) return 1;
    }

    return 0;
}

static void *memory_move(void *dst, const void *src, size_t n)
{
    if (src < dst) {
        for (size_t i = n; i > 0; i--)
            ((byte *)dst)[i - 1] = ((byte *)src)[i - 1];
    } else {
        for (size_t i = 0; i < n; i++)
            ((byte *)dst)[i] = ((byte *)src)[i];
    }

    return dst;
}

/**
 * Copies the memory from one pointer to another.
 *
 * dst - pointer to array where data will be copied to
 * src - pointer to array where data is copied from
 * n - number of bytes to be copied
 *
 * return void* - pointer to destination 
 */
void *memcpy(void *dst, const void *src, size_t n);

/**
 * Moves memory from source to destination.
 * Can move overlaping blocks of memory which means it is safer than memcpy.
 *
 * dst - pointer to array where data will be copied to
 * src - pointer to array where data is copied from
 * n - number of bytes to be copied
 *
 * returns void* - pointer to destination
 */
void *memmove(void *dst, const void *src, size_t n);

/**
 * Sets first `n` characters of `dst` to `c`.
 *
 * dst - pointer to array of memory to be set
 * c - character that the memory will be set to
 * n - number of characters to be set
 *
 * return void* - pointer to the set memory
 */
void *memset(void *dst, int c, size_t n);

/**
 * Compares the first `n` bytes of of `b1` and `b2`.
 *
 * b1 - first block of memory to compare with
 * b2 - second block of memery to compare with
 * n - number of bytes of each block to compare
 *
 * return int - status of compared memory
 *              <0 - first non equal byte has a lower value in `b1`
 *              0  - both blocks of memory are equal
 *              >0 - first non equal byte has a lower value in `b2`
 */
int memcmp(const void *b1, const void *b2, size_t n);

NONNULL_END
