#include "Tilelayer.h"
#include "MapFile.h"
#include <lua.hpp>
#include <assert.h>
#include "TiledLua.h"
#include <luabind\luabind.hpp>

using namespace Tiled;

CTileLayer::CTileLayer(const luabind::object& tilelayer, const CMapFile& mapFile)
{
	if (!tilelayer.is_valid() || luabind::type(tilelayer) != LUA_TTABLE)
		return;

	SetWidth(mapFile.GetWidth());
	SetHeight(mapFile.GetHeight());

	// For some stupid reason the following 2 lines of code are not equivilent to
	// this one line: tilelayer["properties"].push(tilelayer.interpreter())
	// and ends up with ReadProperties not getting a table at the top of the stack.
	const luabind::object properties(tilelayer["properties"]);
	// STK: --
	properties.push(tilelayer.interpreter());
	// STK: -- table

	ReadProperties(tilelayer.interpreter(), this);
	lua_pop(tilelayer.interpreter(), 1);
	// STK: --

	const luabind::object data = tilelayer["data"];
	if (!data.is_valid())
		return;

	m_data.resize(GetHeight(), std::vector<size_t>(GetWidth(), 0));

	// Store the value of each key from Lua, which are in a 1D array, into a C++ 2D vector.
	size_t row = 0;
	for (luabind::iterator iter = luabind::iterator(tilelayer["data"]), end; iter != end; ++row)
	{
		for (size_t col = 0;col < GetWidth(); ++col)
			m_data[row][col] = luabind::object_cast<size_t>(*iter++);
	}
}

size_t CTileLayer::GetDataVal(size_t row, size_t col)
{
	if (!m_data.empty() && row < m_data.size() && col < m_data.front().size())
		return m_data[row][col];
	return 0;
}
