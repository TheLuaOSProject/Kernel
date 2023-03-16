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

typedef struct [[gnu::packed]] {
    qword rax, rbx, rcx, rdx, rsi, rdi, rbp, r8, r9, r10, r11, r12, r13, r14, r15;
    qword rflags, rip, cs, ss, ds, es, fs, gs;
    qword cr0, cr2, cr3, cr4;
    qword rsp;
    qword error, interrupt_number;
} CPUContext;

static inline uint64_t ticks2us(uint64_t x)
{ return (x >> 1) + (x >> 2) + (x >> 4) + (x >> 6) + (x >> 7) + (x >> 9) + (x >> 13) + (x >> 14) + (x >> 16) + (x >> 17) + (x >> 18); }
