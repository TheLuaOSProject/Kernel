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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdnoreturn.h>

#if __STDC_VERSION__ > 201710L
#   define C2X true
#else
#   define C2X false
#endif


#define closed_enum enum [[clang::enum_extensibility(closed)]]

#define pragma(...) _Pragma(#__VA_ARGS__)
#define asm __asm__ __volatile__

#define NONNULL_BEGIN    pragma(clang assume_nonnull begin)
#define NONNULL_END      pragma(clang assume_nonnull end)

#define nullable _Nullable
#define nonnull _Nonnull

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

typedef int8_t sbyte;
typedef int16_t sword;
typedef int32_t sdword;
typedef int64_t sqword;

typedef uintptr_t   ptr;
typedef intptr_t    sptr;

inline noreturn void halt()
{
    while(true) asm (
        "CLI\n"
        "HLT\n"
    );
    __builtin_unreachable();
}

qword _limine__virt_to_phys(qword virt);
qword _limine__phys_to_virt(qword phys);

#define phys(value) _limine__virt_to_phys((qword)(value))
#define virt(value, ...) (__VA_OPT__((__VA_ARGS__*)) (qword) _limine__phys_to_virt(value))
