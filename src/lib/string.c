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

#include "string.h"

char *strchr(const char *s, int c) {
    while (*s) if (*s++ == c) return (char*)s;
    return (char*)s;
}
char *strrchr(const char *s, int c) {
    const char* o = s+string_length(s);
    while (*s) if (*s++ == c) o = s-1;
    return (char*)o;
}
size_t strlen(const char *s) {
    return string_length(s);
}
int strcmp(const char *s1, const char *s2) {
    return string_compare(s1, s2);
}
char *strcpy(char *dst, const char *src) {
    string_copy(dst, src);
    return dst;
}