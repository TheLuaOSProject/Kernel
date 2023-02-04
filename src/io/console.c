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

#include "console.h"

#include <limine.h>

#include "string.h"

void    write(const char *str, size_t len), write_char(char c), print(const char *str), printf(const char *str, ...),
        success(const char *str), info(const char *str), warning(const char *str), error(const char *str), fatal(const char *str);

define_module(console) {
    .write      = write,
    .write_char = write_char,
    .print      = print,
    .printf     = printf,
    .success    = success,
    .info       = info,
    .warning    = warning,
    .error      = error,
    .fatal      = fatal
};

static const volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST
};

static struct limine_terminal *terminal;

static void initalise_terminal()
{
    if (terminal != nullptr) return;

    if (terminal_request.response == nullptr || terminal_request.response->terminal_count < 1)
        halt();

    terminal = terminal_request.response->terminals[0];
}

void write(const char *str, size_t len)
{
    initalise_terminal();

    terminal_request.response->write(terminal, str, len);
}

void write_char(char c)
{
    initalise_terminal();

    terminal_request.response->write(terminal, &c, 1);
}

void print(const char *str)
{
    initalise_terminal();

    terminal_request.response->write(terminal, str, string_length(str));
}

void printf(const char *str, ...)
{
    initalise_terminal();

    (void)str;

    // va_list args;
    // va_start(args, str);
    // terminal_request.response->vprintf(terminal, str, args);
    // va_end(args);

    return;
}

void success(const char *str)
{
    initalise_terminal();

    print("\x1b[32m[SUCCESS]\x1b[0m ");
    print(str);
    print("\n");
}

void info(const char *str)
{
    initalise_terminal();

    print("[INFO] ");
    print(str);
    print("\n");
}

void warning(const char *str)
{
    initalise_terminal();

    print("\x1b[33m[WARNING]\x1b[0m ");
    print(str);
    print("\n");
}

void error(const char *str)
{
    initalise_terminal();

    print("\x1b[31m[ERROR]\x1b[0m ");
    print(str);
    print("\n");
}

void fatal(const char *str)
{
    initalise_terminal();

    print("\x1b[31m[FATAL]\x1b[0m ");
    print(str);
    print("\n");
    halt();
}

