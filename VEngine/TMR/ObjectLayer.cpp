#include "ObjectLayer.h"
#include <lua.hpp>
#include <assert.h>
#include <algorithm>

#include "TiledLua.h"
#include <luabind\luabind.hpp>

using namespace Tiled;

CObjectLayer::CObjectLayer(void)
{

}

void CObjectLayer::ReadMapFile(CMapFile* mapFile, lua_State* L, size_t layer)
{


	luabind::object data = luabind::call_function<luabind::object>(L, "GetLayerObject", layer);
	data.push(L);
	// STK: -- table
	m_properties = GetProperties(L);
	lua_pop(L, 1);
	// STK: --

	const size_t objects = luabind::call_function<size_t>(L, "GetNumOfObjLayerObjects", layer);
	for (size_t i = 1; i <= objects; ++i)
	{
		luabind::object obj = luabind::call_function<luabind::object>(L, "GetObjLayerObject", layer, i);
		m_objects.push_back(TiledObject(obj));
	}
}

std::string CObjectLayer::Property(const std::string& prop)
{
	for(auto iter = m_properties.begin(); iter != m_properties.end(); ++iter)
		if (iter->first == prop)
			return iter->second;
	return "";
}