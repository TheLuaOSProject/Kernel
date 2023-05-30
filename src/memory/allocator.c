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

#include "luck/memory/allocator.h"
#include "luck/memory/manager.h"
#include "luck/memory/magazines.h"
#include "luck/io/log.h"

struct ArenaAllocator create_arena_allocator(size_t maxsiz, byte (*nullable placement)[maxsiz])
{
    if (placement == nullptr) {
        /*TODO: Request magazines(?)*/
    }

    return (struct ArenaAllocator) {
        .capacity = maxsiz,
        .reserved = (byte (*nonnull)[maxsiz])placement
    };
}

void *nullable allocate(struct Allocator *alloc, size_t siz, size_t n)
{
    $debug("Allocating {}x{} ({}) bytes of memory using allocator {}", siz, n, siz * n, alloc);
    return alloc->allocate(siz, n);
}

void allocation_free(struct Allocator *alloc, void *nullable *nonnull ptr)
{
    $debug("Freeing pointer at {} using allocator {}", *ptr, alloc);
    if (*ptr == nullptr) return;

    alloc->free((void *nonnull)*ptr);

    *ptr = nullptr;
}
