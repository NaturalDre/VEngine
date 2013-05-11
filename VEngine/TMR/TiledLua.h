#ifndef TILEDLUA_H
#define TILEDLUA_H

#include <string>
#include <map>
#include <lua.hpp>

struct lua_State;
namespace Tiled
{
	// table.properties; NOTE: Table must be at top of stack before call.
	std::map<const std::string, const std::string> GetProperties(lua_State* L);
	// \note The table is expected to be at the top of the stack.
	std::string GetTableValueStr(lua_State* L, const std::string& key);
	float GetTableValueF(lua_State* L, const std::string& key);

}

#endif