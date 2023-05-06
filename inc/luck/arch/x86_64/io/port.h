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
 * @file port.h
 * @brief I/O with I/O system ports.
 */

#pragma once

#include "common.h"

NONNULL_BEGIN

/** 
 * @brief Read in byte.
 *
 * Reads in a byte from the given I/O @c port.
 *
 * @param port Address of port to read from.
 *
 * @retval byte Data from port.
 */ 
byte port_in_byte(word port);

/** 
 * @brief Output a byte.
 *
 * Writes out @c data to the given I/O @c port.
 *
 * @param port Address of port to output to.
 * @param data Data to be output.
 *
 * @retval void
 */
void port_out_byte(word port, byte data);

/**
 * @brief Read in word.
 *
 * Reads in a word from the given I/O @c port.
 *
 * @param port Address of port to read from.
 *
 * @retval Data read from port.
 */
word port_in_word(word port);

/**
 * @brief Output a word.
 *
 * Outputs a word of data to the specified I/O port.
 *
 * @param port Address of port to output to.
 * @param data Data to be output.
 *
 * @retval void
 */
void port_out_word(word port, word data);

NONNULL_END
