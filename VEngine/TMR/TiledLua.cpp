#include "TiledLua.h"
#include <assert.h>

//using namespace Tiled;

namespace Tiled
{

	std::map<const std::string, const std::string> GetProperties(lua_State*L)
	{
		// STK: -- table1
		lua_pushstring(L, "properties");
		// STK: -- table1 string
		lua_rawget(L, -2);
		// STK: -- table1 table2?
		if (!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			// STL: -- table1
			return std::map<const std::string, const std::string>();
		}
		// STK: -- table1 table2

		lua_insert(L, 1);
		// STK: table2 -- table1 
		lua_pushnil(L);
		// STK: table2 -- table1 keyNil
		std::map<const std::string, const std::string> props;
		while(lua_next(L, 1))
		{
			// STK: table2 -- table1 keyString? valueString?
			if (!lua_isstring(L, -2))
			{
				lua_pop(L, 2);
				// STK: table2 -- table1
				lua_remove(L, 1);
				// STK: -- table
				throw(std::exception("A key in properties is a non string value."));
			}
			else if(!lua_isstring(L, -1))
			{
				lua_pop(L, 2);
				// STK: table2 -- table1
				lua_remove(L, 1);
				// STK: -- table
				throw(std::exception("A value in properties contains a non string value."));
			}
			// STK: table2 -- table1 keyString valueString
			props.insert(std::pair<const std::string, const std::string>(lua_tostring(L, -2),lua_tostring(L, -1)));
			lua_pop(L, 1);
			// STK: table2 -- table1 keyString
		}
		// STK: table2 -- table1
		lua_remove(L, 1);
		// STK: -- table1
		return std::move(props);
	}

	size_t DataValue(lua_State* L, size_t layer, size_t index)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetLayerDataVal");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("Could not get function GetLayerDataVal"));
		}
		// STK: func
		lua_pushinteger(L, layer);
		lua_pushinteger(L, index);
		// STK: func int int
		if (lua_pcall(L, 2, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if(!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		// STK:
		return val;
	}

	size_t GetNumOfTilesets(lua_State* L)
	{
		assert(L != nullptr);

		lua_getglobal(L, "GetNumberOfTilesets");
		// STK: func?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception("GetNumberOfTilesets could not be found."));
		}
		// STK: func
		if (lua_pcall(L, 0, 1, 0))
		{
			const char* error = lua_tostring(L, -1);
			lua_pop(L, 1);
			throw(std::exception(error));
		}
		// STK: int?
		if (!lua_isnumber(L, -1))
		{
			lua_pop(L, 1);
			return 0;
		}
		// STK: int
		int val = lua_tointeger(L, -1);
		lua_pop(L, 1);
		return val;
	}
}