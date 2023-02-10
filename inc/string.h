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

NONNULL_BEGIN

static size_t string_length(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

static int string_compare(const char *str1, const char *str2)
{
    size_t len1 = string_length(str1);
    size_t len2 = string_length(str2);
    size_t len = len1 < len2 ? len1 : len2;
    for (size_t i = 0; i < len; i++) {
        if (str1[i] < str2[i]) return -1;
        if (str1[i] > str2[i]) return 1;
    }
    if (len1 < len2) return -1;
    if (len1 > len2) return 1;
    return 0;
}

static void string_copy_n(char *dest, const char *src, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    dest[n] = '\0';
}

static void string_copy(char *dest, const char *src)
{
    size_t len = string_length(src);
    string_copy_n(dest, src, len);
}

static void string_concatenate_n(char *dest, const char *src, size_t n)
{
    size_t len = string_length(dest);
    string_copy_n(dest + len, src, n);
}

static void string_concatenate(char *dest, const char *src)
{
    size_t len = string_length(src);
    string_concatenate_n(dest, src, len);
}

//struct FormatSpecifier {
//    char fill, align, sign, fill_char, type;
//    bool group, use_alt_form;
//    dword width;
//};
//
//#define _string__formatters(X) \
//    X(char, char) \
//    X(string, const char*) \
//    X(signed8, signed char) \
//    X(signed16, short) \
//    X(signed32, int) \
//    X(signedptr, long) \
//    X(signed64, long long) \
//    X(unsigned8, unsigned char) \
//    X(unsigned16, unsigned short) \
//    X(unsigned32, unsigned int) \
//    X(unsignedptr, unsigned long) \
//    X(unsigned64, unsigned long long) \
//
//#define _string__defines(name, type) void _string_##name(const char *dest, size_t length, type value);
//_string__formatters(_string__defines)
//#undef _string__defines
//
//#define _string__eachtype_cb(name, type) , type: _string_##name
//
//#define _string__one(_, argument) \
//    ({ __auto_type _argument = (argument); _Generic(_argument _string__formatters(_string__eachtype_cb))(_dest, _length, _fmt, _argument); })
//
//
//int _string_format(char *dest, size_t length, const char *fmt, ...);
//#define string_format(dest, length, fmt, ...) ({ char *_dest = (dest); size_t _length = (length); const char *_fmt = (fmt); foreach(_string__one, _ __VA_OPT__(,) __VA_ARGS__); dest; })
//
//static void v()
//{
//    char buf[256] = {0};
//    string_format(buf, 256, "{} + {} = {}", 1, 1, 1 + 1);
//}

NONNULL_END
