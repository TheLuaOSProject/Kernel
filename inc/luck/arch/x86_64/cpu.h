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

//Used to store the state of the CPU, filled by an interrupt, passed to the handler
typedef struct [[gnu::packed]] {
    qword rax, rbx, rcx, rdx, rsi, rdi, rbp, r8, r9, r10, r11, r12, r13, r14, r15;
    qword rflags, rip, cs, ss, ds, es, fs, gs;
    qword cr0, cr2, cr3, cr4;
    qword rsp;
    qword error;
} CPUContext;
