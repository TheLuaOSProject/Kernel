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

#define attribute(...) __attribute__((__VA_ARGS__))

#define inline attribute(always_inline) static inline

#define pragma(...) _Pragma(#__VA_ARGS__)

#define ASSUME_NONNULL_BEGIN    pragma(clang assume_nonnull begin)
#define ASSUME_NONNULL_END      pragma(clang assume_nonnull end)

#define nullable _Nullable
#define nonnull _Nonnull
#define packed  attribute(packed)

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

typedef int8_t sbyte;
typedef int16_t sword;
typedef int32_t sdword;
typedef int64_t sqword;



inline noreturn void halt()
{
    while(true) asm volatile(
        "CLI\n"
        "HLT\n"
    );
    __builtin_unreachable();
}
