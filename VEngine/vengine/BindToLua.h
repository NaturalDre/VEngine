#ifndef BINDTOLUA_H
#define BINDTOLUA_H

#include <lua.hpp>

void BindCPPToLua(lua_State* L);
void ProvideGlobals(lua_State* L);
#endif