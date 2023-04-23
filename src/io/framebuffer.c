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

#define OLIVEC_IMPLEMENTATION
#include "luck/io/framebuffer.h"

#include "lj-libc/limits.h"
#include <LuaJIT/src/lauxlib.h>

#define CANVAS_T "OliveCanvas"

static struct limine_framebuffer *nullable framebuffer = nullptr;

Olivec_Canvas framebuffer_init(struct limine_framebuffer *fb)
{
    framebuffer = fb;
    return olivec_canvas(fb->address, fb->width, fb->height, fb->width);
}

static int libframebuffer_canvas_fill(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    dword colour = luaL_checkinteger(L, 2);

    olivec_fill(*canvas, colour);

    return 0;
}

static int libframebuffer_canvas_set_pixel(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    dword x = luaL_checkinteger(L, 2);
    dword y = luaL_checkinteger(L, 3);
    dword colour = luaL_checkinteger(L, 4);

    if (x >= canvas->width || y >= canvas->height) {
        lua_pushnil(L);
        lua_pushstring(L, "pixel out of bounds");
        return 2;
    }

    OLIVEC_PIXEL(*canvas, x, y) = colour;

    return 0;
}

static int libframebuffer_canvas_get_pixel(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    dword x = luaL_checkinteger(L, 2);
    dword y = luaL_checkinteger(L, 3);

    if (x >= canvas->width || y >= canvas->height) {
        lua_pushnil(L);
        lua_pushstring(L, "pixel out of bounds");
        return 2;
    }

    lua_pushinteger(L, OLIVEC_PIXEL(*canvas, x, y));

    return 1;
}

static int libframebuffer_canvas_draw_line(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    auto x1 = (sdword)luaL_checkinteger(L, 2);
    auto y1 = (sdword)luaL_checkinteger(L, 3);
    auto x2 = (sdword)luaL_checkinteger(L, 4);
    auto y2 = (sdword)luaL_checkinteger(L, 5);
    dword colour = luaL_checkinteger(L, 6);

    olivec_line(*canvas, x1, y1, x2, y2, colour);

    return 0;
}

static int libframebuffer_canvas_draw_rect(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    auto x = (sdword)luaL_checkinteger(L, 2);
    auto y = (sdword)luaL_checkinteger(L, 3);
    auto w = (sdword)luaL_checkinteger(L, 4);
    auto h = (sdword)luaL_checkinteger(L, 5);
    dword colour = luaL_checkinteger(L, 6);

    olivec_rect(*canvas, x, y, w, h, colour);

    return 0;
}

static int libframebuffer_canvas_draw_circle(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    auto x = (sdword)luaL_checkinteger(L, 2);
    auto y = (sdword)luaL_checkinteger(L, 3);
    auto r = (sdword)luaL_checkinteger(L, 4);
    dword colour = luaL_checkinteger(L, 5);

    olivec_circle(*canvas, x, y, r, colour);

    return 0;
}

static int libframebuffer_canvas_draw_text(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    auto x = (sdword)luaL_checkinteger(L, 2);
    auto y = (sdword)luaL_checkinteger(L, 3);
    const char *text = luaL_checkstring(L, 4);
    dword colour = luaL_checkinteger(L, 5);
    qword size = luaL_checkinteger(L, 6);


    olivec_text(*canvas, text, x, y, olivec_default_font, size, colour);

    return 0;
}

// framebuffer:test_pitch()
static int libframebuffer_test_pitch(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);

    for (size_t i = 0; i < (size_t)-1; i++) {
        canvas->stride = i;
        olivec_fill(*canvas, 0xFFFFFFFF);
    }

    return 0;
}

// function framebuffer:set_pitch(pitch)
static int libframebuffer_set_pitch(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);
    dword pitch = luaL_checkinteger(L, 2);

    canvas->stride = pitch;

    return 0;
}

// function framebuffer:get_dimensions()
static int libframebuffer_get_dimensions(lua_State *L)
{
    Olivec_Canvas *canvas = luaL_checkudata(L, 1, CANVAS_T);

    lua_pushinteger(L, (sqword)canvas->width);
    lua_pushinteger(L, (sqword)canvas->height);

    return 2;
}

static int libframebuffer_create(lua_State *L)
{
    if (framebuffer == nullptr) {
        lua_pushnil(L);
        lua_pushstring(L, "framebuffer not initialized");
        return 2;
    }

    struct limine_framebuffer *fb = framebuffer;
    Olivec_Canvas canvas = olivec_canvas(fb->address, fb->width, fb->height, fb->pitch);

    Olivec_Canvas *canvas_ptr = lua_newuserdata(L, sizeof(Olivec_Canvas));
    *canvas_ptr = canvas;

    luaL_getmetatable(L, CANVAS_T);
    lua_setmetatable(L, -2);

    return 1;
}

static const luaL_Reg libframebuffer_canvas[] = {
    { "fill", libframebuffer_canvas_fill },
    { "set_pixel", libframebuffer_canvas_set_pixel },
    { "get_pixel", libframebuffer_canvas_get_pixel },
    { "draw_line", libframebuffer_canvas_draw_line },
    { "draw_rect", libframebuffer_canvas_draw_rect },
    { "draw_circle", libframebuffer_canvas_draw_circle },
    { "draw_text", libframebuffer_canvas_draw_text },
    { "test_pitch", libframebuffer_test_pitch },
    { "set_pitch", libframebuffer_set_pitch },
    { "get_dimensions", libframebuffer_get_dimensions },
    { nullptr, nullptr }
};

static const luaL_Reg libframebuffer[] = {
    { "create", libframebuffer_create },
    { nullptr, nullptr }
};

int luaopen_framebuffer(lua_State *L)
{
    luaL_newmetatable(L, CANVAS_T);
    // metatable.__index = metatable
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, libframebuffer_canvas, 0);
    lua_pop(L, 1);

    luaL_newlib(L, libframebuffer);
    return 1;
}
