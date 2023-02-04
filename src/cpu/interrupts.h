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

struct IDTEntry {
    word offset_low, selector;
    byte interrupt_stack_table, flags;
    word offset_middle;
    dword offset_high, reserved;
};

struct IDTRegister {
    word limit;
    qword base;
} packed;

declare_module {
    struct IDTEntry descriptor_table[256];
    void *nullable  service_routines[256];

    void (*initalise)(void);
    void (*register_interrupt)(byte interrupt, void *routine, byte flags);
    void (*load)(void);
} interrupts;

ASSUME_NONNULL_END
