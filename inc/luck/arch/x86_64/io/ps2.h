/**
 * Copyright (C) 2023 pitulst
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
 * @file ps2.h
 * @brief Interaction with ps2 I/O.
 *
 * Reads and processes input according to the ps2 specification.
 *
 * @see https://wiki.osdev.org/%228042%22_PS/2_Controller
 */

#pragma once

/**
 * @brief Gets a character from a ps2 input port.
 *
 * @retval char The retrieved character after being processed.
 */
char ps2_getc(void);
