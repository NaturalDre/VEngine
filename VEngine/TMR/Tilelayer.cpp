#include "Tilelayer.h"
#include "MapFile.h"
#include <lua.hpp>
#include <assert.h>
#include "TiledLua.h"
#include <luabind\luabind.hpp>

using namespace Tiled;

CTileLayer::CTileLayer(void)
{

}

bool CTileLayer::ReadMap(lua_State* L, const size_t layerIndex, CMapFile* mapFile)
{
	SetWidth(mapFile->Width());
	SetHeight(mapFile->Height());

	// STK: --
	luabind::object data = luabind::call_function<luabind::object>(L, "GetLayerObject", layerIndex);
	data.push(L);
	// STK: -- table
	m_properties = GetProperties(L);
	lua_pop(L, 1);

	m_data.resize(mapFile->Height(), std::vector<size_t>(mapFile->Width(), 0));

	for (size_t row = 0, element = 1; row < GetHeight(); ++row)
	{
		for (size_t col = 0; col < GetWidth(); ++col)
			m_data[row][col] = DataValue(L, layerIndex, element++);
	}

	return true;
}

size_t CTileLayer::GetDataVal(size_t row, size_t col)
{
	if (!m_data.empty() && row < m_data.size() && col < m_data.front().size())
		return m_data[row][col];
	return 0;
}
