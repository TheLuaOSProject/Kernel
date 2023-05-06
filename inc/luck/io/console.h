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

/**
 * @file console.h
 * @brief Allows I/O with the terminal emulator.
 */

#pragma once

#include "common.h"

#include <limine/limine.h>

NONNULL_BEGIN

/**
 * @brief Initialise the terminal emulator.
 *
 * @retval void
 */
void terminal_init();

/**
 * @brief Writes to the terminal emulator.
 *
 * @param str String that gets written out.
 *
 * @retval void
 */
void console_write(const char *str);

/**
 * @brief Writes a single char to terminal emulator.
 *
 * @param c Character to written out.
 *
 * @retval void
 */
void console_write_char(char c);

NONNULL_END
