#ifndef TILEDLUA_H
#define TILEDLUA_H

#include <string>
#include <map>
#include <lua.hpp>

namespace Tiled
{
	// table.properties; NOTE: Table must be at top of stack before call.
	std::map<const std::string, const std::string> GetProperties(lua_State* L);
	// map.layers[layer].data[index]
	size_t DataValue(lua_State* L, size_t layer, size_t index);
}

#endif