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

#include "common.h"

ASSUME_NONNULL_BEGIN

struct GDTDescriptor {
    word limit, base_low;
    byte base_middle, access, granularity, base_high;
};

struct TSSDescriptor {
    word length, base_low;
    byte base_middle, flag0, flag1, base_high;
    dword base_upper, reserved;
};

struct GlobalDescriptorTable {
    struct GDTDescriptor descriptors[11];
    struct TSSDescriptor task_state_segment;
};

struct GDTRegister {
    word limit;
    dword base;
} packed;

declare_module {
    struct GlobalDescriptorTable    table;
    struct GDTRegister              gdtregister;

    void (*initalise)(void);
} global_descriptor_table;

ASSUME_NONNULL_END
