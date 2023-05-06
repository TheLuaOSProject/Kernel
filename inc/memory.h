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

/**
 * @file memory.h
 * @brief Required memory management functions.
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
 * @brief Copies memory.
 *
 * Copies memory from one pointer to another without checking for overlapping
 * blocks of memory.
 *
 * @param dst Pointer to array where data will be copied to.
 * @param src Pointer to array where data is copied from.
 * @param n Number of bytes to be copied.
 *
 * @retval void* Pointer to destination.
 */
void *memcpy(void *dst, const void *src, size_t n);

/**
 * @brief Moves memory.
 *
 * Moves memory from source to destination. Can move overlaping blocks of memory which means it is safer than memcpy.
 *
 * @param dst Pointer to array where data will be copied to.
 * @param src Pointer to array where data is copied from.
 * @param n Number of bytes to be copied.
 *
 * @retval void* Pointer to destination.
 */
void *memmove(void *dst, const void *src, size_t n);

/**
 * @brief Sets block of memory.
 * 
 * Sets first @c n characters of @c dst to @c c.
 *
 * @param dst Pointer to array of memory to be set.
 * @param c Character that the memory will be set to.
 * @param n Number of characters to be set.
 *
 * @retval void* Pointer to the set memory.
 */
void *memset(void *dst, int c, size_t n);

/**
 * @brief Compares two blocks of memory.
 *
 * Compares the first @c n bytes of of @c b1 and @c b2.
 *
 * @param b1 First block of memory to compare with.
 * @param b2 Second block of memery to compare with.
 * @param n Number of bytes of each block to compare.
 *
 * @retval void* Status of compared memory
 *         - <0 first non equal byte has a lower value in @c b1
 *         - 0 both blocks of memory are equal
 *         - >0 first non equal byte has a lower value in @c b2
 */
int memcmp(const void *b1, const void *b2, size_t n);

NONNULL_END
