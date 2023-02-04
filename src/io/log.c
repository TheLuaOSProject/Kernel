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

#include "log.h"
#include "common.h"
#include "string.h"

#include "port.h"

static void log_write(const char *str, size_t len), log_print(const char *str), log_printf(const char *str, ...);

define_module(log) {
    .write = log_write,
    .print = log_print,
    .printf = log_printf
};

static void log_write(const char *str, size_t len)
{
    for (size_t i = 0; i < len; i++)
        port.write_byte(QEMU_LOG_PORT, str[i]);
}

static void log_print(const char *str)
{ log_write(str, string_length(str)); }

static void log_printf(const char *str, ...)
{
    (void)str;
    return;
    // va_list args;
    // va_start(args, str);
    // char *buf = string_format(str, args);
    // va_end(args);
    // log_print(buf);
    // free(buf);
}
