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

#include "olive.h"

#include "common.h"

#include <limine/limine.h>

#include <lua.h>

NONNULL_BEGIN

/**
 * Initialises a framebuffer.
 * Uses olivec under the hood.
 *
 * return Olivec_canvas - refer to https://github.com/tsoding/olive.c
 */
Olivec_Canvas framebuffer_init();

/**
 * Gets the lua table for the framebuffer
 * Used by `luaopen_kernel` to the framebuffer to the `kernel` table.
 */
int luaopen_framebuffer(lua_State *L);

NONNULL_END
