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

void console_write(const char *str, size_t len), console_write_char(char c), console_print(const char *str), console_printf(const char *str, ...);

define_module(console) {
    .write = console_write,
    .write_char = console_write_char,
    .print = console_print,
    .printf = console_printf
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

void console_write(const char *str, size_t len)
{
    initalise_terminal();

    terminal_request.response->write(terminal, str, len);
}

void console_write_char(char c)
{
    initalise_terminal();

    terminal_request.response->write(terminal, &c, 1);
}

void console_print(const char *str)
{
    initalise_terminal();

    terminal_request.response->write(terminal, str, string_length(str));
}

void console_printf(const char *str, ...)
{
    initalise_terminal();

    (void)str;

    // va_list args;
    // va_start(args, str);
    // terminal_request.response->vprintf(terminal, str, args);
    // va_end(args);

    return;
}


