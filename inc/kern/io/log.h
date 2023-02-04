/**
 * Copyright (C) 2023 Amrit Bhogal, pitust
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
#include "kern/macro_util.h"

ASSUME_NONNULL_BEGIN

void _log_level_info(void);
void _log_level_warn(void);
void _log_level_err(void);
void _log_level_panic(void);

void _log_level_common_end(const char* nonnull* nonnull fmtref);
noreturn void _log_level_panic_end(const char* nonnull* nonnull fmtref);

#define _log_level_info_end _log_level_common_end
#define _log_level_warn_end _log_level_common_end
#define _log_level_err_end _log_level_common_end

#define _log__formatters(X) \
    X(char, char) \
    X(string, const char*) \
    X(signed8, signed char) \
    X(signed16, short) \
    X(signed32, int) \
    X(signedptr, long) \
    X(signed64, long long) \
    X(unsigned8, unsigned char) \
    X(unsigned16, unsigned short) \
    X(unsigned32, unsigned int) \
    X(unsignedptr, unsigned long) \
    X(unsigned64, unsigned long long) \

#define _log__defines(name, type) void _log_##name(const char*nonnull *nonnull fmtref, type value);
_log__formatters(_log__defines)
#undef _log__defines

#define _log__eachtype_cb(name, type) , type: _log_##name

#define _log__one(_, argument) \
    { __auto_type _argument = (argument); _Generic(_argument _log__formatters(_log__eachtype_cb))(&_fmt, _argument); }

#define log(level, fmt, ...) do { \
        _log_level_##level(); \
        const char* _fmt = (fmt); \
        foreach(_log__one, _ __VA_OPT__(,) __VA_ARGS__) \
        _log_level_##level##_end(&_fmt); \
    } while (0)

#define info(fmt, ...) log(info, fmt __VA_OPT__(,) __VA_ARGS__)
#define warn(fmt, ...) log(warn, fmt __VA_OPT__(,) __VA_ARGS__)
#define err(fmt, ...) log(err, fmt __VA_OPT__(,) __VA_ARGS__)
#define panic(fmt, ...) log(panic, fmt __VA_OPT__(,) __VA_ARGS__)

ASSUME_NONNULL_END
