/**
 * Copyright (C) 2023 pitust
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
 * @file manager.h
 * @brief Kernel space management for memory.
 */

#pragma once

#include <common.h>

NONNULL_BEGIN

extern qword VIRTUAL_MEMORY_HIGH;
#define VIRTUAL_MEMORY_HIGH ((const qword)VIRTUAL_MEMORY_HIGH)

/// page allocation ///
closed_enum PageType {
    PageType_PAGETABLE,
    PageType_REGULAR
};

/**
 * @brief Allocate a page of memory.
 *
 * @param pty Type of page to be allocated.
 *
 * @retval qword Address to the memory allocated.
 */
qword page_alloc(enum PageType pty);

/// mapping pages ///
void pmap_map(qword addr, qword phys);
void pmap_map_rwx(qword addr, qword phys);

/// kalloc ///
void kalloc_init(void);
void *kalloc(qword size);
void kfree(void *ptr, qword size);

NONNULL_END
