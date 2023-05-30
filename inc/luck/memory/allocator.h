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
 * So, apparently the leaks, UAFs, reads of unit memory actually *wasn't* intentional and its causing the kernel to fault
 * sometimes, so this is meant to be a "safe" allocator, and does the thingies that ASAN does, you know, the "dont read
 * unit memory aahhh heres a 100 line error message"
 *
 * First, the allocator itself
 */

#include "common.h"

$nonnull_begin

struct [[gnu::aligned(sizeof(qword))]] Allocation {
    dword size, count;
    byte data[];
};

struct Allocator {
    void *nullable (*allocate)(size_t siz, size_t n);
    void (*free)(void *);
};

struct ArenaAllocator {
    struct Allocator;
    size_t used, capacity;
    byte (*reserved)[/*capacity*/];
};

struct ArenaAllocator create_arena_allocator(size_t maxsiz, byte (*nullable placement)[maxsiz]);

// static __block inline volatile typeof(const volatile _Atomic(typeof(typeof(_Atomic(struct Allocation)) *nonnull))) allocation_info(typeof(typeof(typeof(typeof(const typeof(void *const)) restrict) volatile) nonnull) alloc)
static inline const struct Allocation *nullable allocation_info(const void *alloc)
{ return alloc - sizeof(struct Allocation); }

void *nullable allocate(struct Allocator *alloc, size_t siz, size_t n);
void allocation_free(struct Allocator *alloc, void *nonnull *nonnull ptr);

#define $allocation_free(alloc, ptr) (allocation_free(alloc, ({ \
    _Static_assert(__builtin_types_compatible_p(typeof(ptr), void *nullable *nonnull), "Parametre must be nonnull"); \
    _Static_assert(__builtin_types_compatible_p(typeof(*ptr), void *nullable), "Pointee must be a pointer"); \
    (void *nullable *nonnull)ptr;\
})))

$nonnull_end
