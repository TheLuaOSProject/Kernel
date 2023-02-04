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

static void write(const char *str, size_t len), print(const char *str), printf(const char *str, ...),
            success(const char *str), info(const char *str), warning(const char *str), error(const char *str), fatal(const char *str);

define_module(log) {
    .write  = write,
    .print  = print,
    .printf = printf,
    .success= success,
    .info   = info,
    .warning= warning,
    .error  = error,
    .fatal  = fatal,
};

static void write(const char *str, size_t len)
{
    for (size_t i = 0; i < len; i++)
        port.write_byte(QEMU_LOG_PORT, str[i]);
}

static void print(const char *str)
{ write(str, string_length(str)); }

static void printf(const char *str, ...)
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

static void success(const char *str)
{
    print("[SUCCESS] ");
    print(str);
    print("\n");
}

static void info(const char *str)
{
    print("[INFO] ");
    print(str);
    print("\n");
}

static void warning(const char *str)
{
    print("[WARNING] ");
    print(str);
    print("\n");
}

static void error(const char *str)
{
    print("[ERROR] ");
    print(str);
    print("\n");
}

static void fatal(const char *str)
{
    print("[FATAL] ");
    print(str);
    print("\n");
}
