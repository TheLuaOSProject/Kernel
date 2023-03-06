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

#include "common.h"
#include "luck/memory/manager.h"

#define LAPIC_BASE 0xfee00000

NONNULL_BEGIN

inline dword lapic_read(dword reg)
{ return *(dword *)(LAPIC_BASE + VIRTUAL_MEMORY_HIGH + reg); }

inline void lapic_write(dword reg, dword val)
{ *(dword *)(LAPIC_BASE + VIRTUAL_MEMORY_HIGH + reg) = val; }



void lapic_init(void);

NONNULL_END
