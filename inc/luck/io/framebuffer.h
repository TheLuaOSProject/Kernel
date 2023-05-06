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

/**
 * @file framebuffer.h
 * @brief Interaction with framebuffers.
 *
 * Supply's functions for creating and controlling framebuffers. It uses olivec
 * to provide functions for representing and controlling the data of the
 * framebuffers.
 *
 * @see https://github.com/tsoding/olive.c
 */

#include "olive.h"

#include "common.h"

#include <limine/limine.h>

#include <lua.h>

NONNULL_BEGIN

/**
 * @brief Initialises a framebuffer.
 *
 * @retval Olivec_canvas @ref https://github.com/tsoding/olive.c
 *
 * @note Uses olivec.
 */
Olivec_Canvas framebuffer_init();

/**
 * @brief Gets the lua table for the framebuffer
 *
 * Used by @c luaopen_kernel to the framebuffer to the @c kernel table.
 *
 * @param L The lua state to add the framebuffer to.
 *
 * @retval int Always 1.
 */
int luaopen_framebuffer(lua_State *L);

NONNULL_END
