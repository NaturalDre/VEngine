#ifndef VENGINESTATICS_H
#define VENGINESTATICS_H

#include <lua.hpp>

void BindCPPToLua(lua_State* L);
void ProvideGlobals(lua_State* L);
void ProvideLevelFactories(lua_State* L);


#endif