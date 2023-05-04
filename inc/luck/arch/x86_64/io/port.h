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

#pragma once

#include "common.h"

NONNULL_BEGIN

/** 
 * read in byte from an I/O port
 *
 * port - address of port to read from
 *
 * return - data from port
 */ 
byte port_in_byte(word port);

/** 
 * output data to an I/O port
 *
 * port - address of port to output to
 * data - data to be output
 *
 * return - void
 */
void port_out_byte(word port, byte data);

/**
 * read in word from an I/O port
 *
 * port - address of port to read from
 *
 * return - data from port
 */
word port_in_word(word port);

/**
 * output data to an I/O port
 *
 * port - address of port to output to 
 * data - data to be output
 *
 * return - void
 */
void port_out_word(word port, word data);

NONNULL_END
