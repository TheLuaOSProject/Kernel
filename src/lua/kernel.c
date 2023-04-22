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

#include <LuaJIT/src/lua.h>
#include "luck/io/log.h"

#include "lj-libc/limits.h"
#include <LuaJIT/src/lauxlib.h>

// kernel.log.info("Hello, world!");

#define lua_write_log(source, line, func, level, fmt, ...) ({ \
        char buf[512] = {};\
        _log_level_##level(); \
        _log_begin(source, integer_to_string(512, buf, line), func); \
        const char* _fmt = (fmt); \
        foreach(_log__one, _ __VA_OPT__(,) __VA_ARGS__) \
        _log_level_##level##_end(&_fmt); \
    })

static int kernel_log_debug(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    struct lua_Debug dbg = {0};
    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "nSl", &dbg);
    lua_write_log(dbg.source, dbg.currentline, dbg.name, debug, msg);
    return LUA_OK;
}

static int kernel_log_info(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    struct lua_Debug dbg = {0};
    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "nSl", &dbg);
    lua_write_log(dbg.source, dbg.currentline, dbg.name, info, msg);
    return LUA_OK;
}

static int kernel_log_warning(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    struct lua_Debug dbg = {0};
    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "nSl", &dbg);
    lua_write_log(dbg.source, dbg.currentline, dbg.name, warning, msg);
    return LUA_OK;
}

static int kernel_log_error(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    struct lua_Debug dbg = {0};
    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "nSl", &dbg);
    lua_write_log(dbg.source, dbg.currentline, dbg.name, error, msg);
    return LUA_OK;
}

static int kernel_log_panic(lua_State *L)
{
    const char *msg = luaL_checkstring(L, 1);
    struct lua_Debug dbg = {0};
    lua_getstack(L, 1, &dbg);
    lua_getinfo(L, "nSl", &dbg);
    lua_write_log(dbg.source, dbg.currentline, dbg.name, panic, msg);
    return LUA_OK;
}

static const luaL_Reg libkernel_log[] = {
    { "debug", kernel_log_debug },
    { "info", kernel_log_info },
    { "warning", kernel_log_warning },
    { "error", kernel_log_error },
    { "panic", kernel_log_panic },
    { nullptr, nullptr }
};

static const luaL_Reg libkernel[] = {
    { nullptr, nullptr }
};

int luaopen_kernel(lua_State *L)
{
    luaL_newlib(L, libkernel);
    lua_setglobal(L, "kernel");

    lua_getglobal(L, "kernel");
    luaL_newlib(L, libkernel_log);
    lua_setfield(L, -2, "log");

    return 0;
}
