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

#define QEMU_LOG_PORT 0x3F8

declare_module {
    void (*write)(const char *str, size_t len);
    void (*print)(const char *str);
    void (*printf)(const char *str, ...);

    void (*success)(const char *str);
    void (*info)(const char *str);
    void (*warning)(const char *str);
    void (*error)(const char *str);
    void (*fatal)(const char *str);
} log;

ASSUME_NONNULL_END
