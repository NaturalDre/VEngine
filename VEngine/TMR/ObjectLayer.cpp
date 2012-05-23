#include "ObjectLayer.h"
#include <lua.hpp>
#include <assert.h>
#include "TiledLua.h"

using namespace Tiled;

//bool PushObject(lua_State* L, size_t layer, size_t index);
//bool PushObjectLayer(lua_State* L, size_t layer);
//size_t NumberOfObjects(lua_State* L, size_t layer);
//std::map<const std::string, const std::string> GetProperties(lua_State*L);

CObjectLayer::CObjectLayer(void)
{

}

void CObjectLayer::ReadMapFile(CMapFile* mapFile, lua_State* L, size_t layer)
{
	const size_t objects = NumberOfObjects(L, layer);
	if(PushLayer(L, layer))
	{
		// STK: Table
		m_properties = GetProperties(L);
		// STK: Table
		lua_pop(L, 1);
		// STK:
	}
	for (size_t i = 1; i <= objects; ++i)
	{
		bool success = PushTiledObject(L, layer, i);
		m_objects.push_back(TiledObject::CreateFromLua(L));
		lua_pop(L, 1);
		//m_properties = GetProperties(L);

	}
}

//bool PushObject(lua_State* L, size_t layer, size_t index)
//{
//		assert(L != nullptr);
//
//		lua_getglobal(L, "GetObjLayerObject");
//		// STK: func?
//		if (!lua_isfunction(L, -1))
//		{
//			lua_pop(L, 1);
//			throw(std::exception("Could not get function GetLayerDataVal"));
//		}
//		// STK: func
//		lua_pushinteger(L, layer);
//		lua_pushinteger(L, index);
//		// STK: func int int
//		if (lua_pcall(L, 2, 1, 0))
//		{
//			const char* error = lua_tostring(L, -1);
//			lua_pop(L, 1);
//			throw(std::exception(error));
//		}
//		// STK: table?
//		if(!lua_istable(L, -1))
//		{
//			lua_pop(L, 1);
//			return false;
//		}
//
//		return true;
//};
//
//bool PushObjectLayer(lua_State* L, size_t layer)
//{
//		assert(L != nullptr);
//
//		lua_getglobal(L, "GetLayerObject");
//		// STK: func?
//		if (!lua_isfunction(L, -1))
//		{
//			lua_pop(L, 1);
//			throw(std::exception("Could not get function GetLayerObject"));
//		}
//		// STK: func
//		lua_pushinteger(L, layer);
//		//lua_pushinteger(L, index);
//		// STK: func int int
//		if (lua_pcall(L, 1, 1, 0))
//		{
//			const char* error = lua_tostring(L, -1);
//			lua_pop(L, 1);
//			throw(std::exception(error));
//		}
//		// STK: table?
//		if(!lua_istable(L, -1))
//		{
//			lua_pop(L, 1);
//			return false;
//		}
//
//		return true;
//}
//
//size_t NumberOfObjects(lua_State* L, size_t layer)
//{
//		assert(L != nullptr);
//
//		lua_getglobal(L, "GetNumOfObjLayerObjects");
//		// STK: func?
//		if (!lua_isfunction(L, -1))
//		{
//			lua_pop(L, 1);
//			return 0;
//		}
//		// STK: func
//		lua_pushinteger(L, layer);
//		// STK: func int
//		if (lua_pcall(L, 1, 1, 0))
//		{
//			const char* error = lua_tostring(L, -1);
//			lua_pop(L, 1);
//			throw(std::exception(error));
//		}
//		// STK: int?
//		if (!lua_isnumber(L, -1))
//		{
//			lua_pop(L, 1);
//			return 0;
//		}
//		// STK: int
//		int val = lua_tointeger(L, -1);
//		lua_pop(L, 1);
//		return val;
//}
//
//std::map<const std::string, const std::string> GetProperties(lua_State*L)
//{
//	// STK: table1 --
//	lua_pushstring(L, "properties");
//	// STK: table1 -- string
//	lua_rawget(L, 1);
//	// STK: table1 -- table2?
//	if (!lua_istable(L, -1))
//	{
//		lua_pop(L, 1);
//		// STL: table1 --
//		throw(std::exception("Table has not 'properties' key."));
//	}
//	// STK: table1 -- table2
//	lua_insert(L, 1);
//	// STK: table2 table1 --
//	lua_pushnil(L);
//	// STK: table2 table1 -- nil
//	std::map<const std::string, const std::string> props;
//	while(lua_next(L, 1))
//	{
//		// STK: table2 table1 -- string? string?
//		if (!lua_isstring(L, -2))
//			throw(std::exception("A key in properties is a non string value."));
//		else if(!lua_isstring(L, -1))
//			throw(std::exception("A key in properties returned a non string value."));
//		// STK: table2 table1 -- string string
//		props.insert(std::pair<const std::string, const std::string>(lua_tostring(L, -2),lua_tostring(L, -1)));
//		//props[lua_tostring(L, -2)] = lua_tostring(L, -1);
//		lua_pop(L, 1);
//
//	}
//	// STK: table2 table1 --
//	lua_remove(L, 1);
//	// STK: table1
//	return std::move(props);
//}