#include "ObjectLayer.h"
#include <lua.hpp>
#include <assert.h>
#include <algorithm>

#include "TiledLua.h"

using namespace Tiled;

CObjectLayer::CObjectLayer(void)
{

}

void CObjectLayer::ReadMapFile(CMapFile* mapFile, lua_State* L, size_t layer)
{
	const size_t objects = NumberOfObjects(L, layer);
	if(PushLayer(L, layer))
	{
		// STK: Table
		m_properties = Tiled::GetProperties(L);
		// STK: Table
		lua_pop(L, 1);
		// STK:
	}
	for (size_t i = 1; i <= objects; ++i)
	{
		bool success = PushTiledObject(L, layer, i);
		m_objects.push_back(TiledObject::CreateFromLua(L));
		lua_pop(L, 1);
	}
}

std::string CObjectLayer::Property(const std::string& prop)
{
	for(auto iter = m_properties.begin(); iter != m_properties.end(); ++iter)
		if (iter->first == prop)
			return iter->second;
	return "";
}