#include <vengine\Tiled.h>
#include <lua.hpp>
#include <vengine\Utility.h>
#include <vengine\Script\LuaScript.h>

namespace Tiled
{
	////////////////////////////////
	////////// TILED OBJECT ////////
	////////////////////////////////

	TiledObject::TiledObject(TiledObject&& rhs)
				: name(rhs.name)
				, type(rhs.type)
				, x(rhs.x)
				, y(rhs.y)
				, width(rhs.width)
				, height(rhs.height)
				, properties(std::move(rhs.properties)) { }


	TiledObject ToTiledObject(lua_State* L)
	{
		// STK: table? --
		if (!lua_istable(L, 1))
			throw(std::exception("Bottom object on the stack is not a table."));
		// STK: table --
		TiledObject obj;
		obj.name = VE::Utility::GetStringVal("name", L);
		obj.type = VE::Utility::GetStringVal("type", L);
		obj.x = VE::Utility::GetFloatVal("x", L);
		obj.y = VE::Utility::GetFloatVal("y", L);
		obj.width = VE::Utility::GetFloatVal("width", L);
		obj.height = VE::Utility::GetFloatVal("height", L);
		obj.properties = std::move(Tiled::GetProperties(L));
		return obj;
	}

	std::map<const std::string, std::string> GetProperties(lua_State*L)
	{
		// STK: table1 --
		lua_pushstring(L, "properties");
		// STK: table1 -- string
		lua_rawget(L, 1);
		// STK: table1 -- table2?
		if (!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			// STL: table1 --
			throw(VE::LuaError("Table has not 'properties' key."));
		}
		// STK: table1 -- table2
		lua_insert(L, 1);
		// STK: table2 table1 --
		lua_pushnil(L);
		// STK: table2 table1 -- nil
		std::map<const std::string, std::string> props;
		while(lua_next(L, 1))
		{
			// STK: table2 table1 -- string? string?
			if (!lua_isstring(L, -2))
				throw(VE::LuaError("A key in properties is a non string value."));
			else if(!lua_isstring(L, -1))
				throw(VE::LuaError("A key in properties returned a non string value."));
			// STK: table2 table1 -- string string
			props[lua_tostring(L, -2)] = lua_tostring(L, -1);
			lua_pop(L, 1);

		}
		// STK: table2 table1 --
		lua_remove(L, 1);
		// STK: table1
		return std::move(props);
	}

	bool IsScriptName(const std::string& str)
	{
		const int ret = str.find("script_");
		if (ret)
			return false;
		return true;
	}
}