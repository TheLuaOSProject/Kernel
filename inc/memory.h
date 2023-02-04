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

static size_t memory_copy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return n;
}

static size_t memory_set(void *dest, int c, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        ((char *)dest)[i] = c;
    }
    return n;
}

static int memory_compare(const void *s1, const void *s2, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (((char *)s1)[i] < ((char *)s2)[i]) return -1;
        if (((char *)s1)[i] > ((char *)s2)[i]) return 1;
    }
    return 0;
}
