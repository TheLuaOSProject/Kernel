#include <LuaJIT/src/lua.h>
#include "luck/io/log.h"

typedef struct luaL_Reg {
    const char *name;
    lua_CFunction func;
} luaL_Reg;

#define luaL_newlibtable(L, l) lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)
#define luaL_newlib(L, l)   (luaL_newlibtable(L, l), luaL_setfuncs(L, l, 0))

void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup);

// LUALIB_API void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup)
// {
//   luaL_checkstack(L, nup, "too many upvalues");
//   for (; l->name; l++) {
//     int i;
//     for (i = 0; i < nup; i++)  /* Copy upvalues to the top. */
//       lua_pushvalue(L, -nup);
//     lua_pushcclosure(L, l->func, nup);
//     lua_setfield(L, -(nup + 2), l->name);
//   }
//   lua_pop(L, nup);  /* Remove upvalues. */
// }

static int func(lua_State *L) {
    lua_Integer d = lua_tointeger(L, 1);
    info("D: {}", d);
    return LUA_OK;
}

static luaL_Reg llc[] = {
    {"func", func},
    {nullptr, nullptr}
};

void luaopen_llc(lua_State* L) {
    lua_createtable(L, 0, 1);
    int i = lua_gettop(L);
    lua_pushcfunction(L, func);
    lua_setfield(L, i, "func");
    lua_setglobal(L, "_llchannel");
}
