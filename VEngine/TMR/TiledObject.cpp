#include "TiledObject.h"
#include <lua.hpp>

using namespace Tiled;

std::string GetStringVal(const std::string& key, lua_State* L);
float GetFloatVal(const std::string& key, lua_State* L);
std::map<const std::string, std::string> GetProperties(lua_State*L);

TiledObject::TiledObject(TiledObject&& rhs)
	: name(rhs.name)
	, type(rhs.type)
	, x(rhs.x)
	, y(rhs.y)
	, width(rhs.width)
	, height(rhs.height)
	, properties(std::move(rhs.properties)) { }


TiledObject TiledObject::CreateFromLua(lua_State* L)
{
	// STK: table? --
	if (!lua_istable(L, 1))
		throw(std::exception("Bottom object on the stack is not a table."));
	// STK: table --
	TiledObject obj;
	obj.name = GetStringVal("name", L);
	obj.type = GetStringVal("type", L);
	obj.x = GetFloatVal("x", L);
	obj.y = GetFloatVal("y", L);
	obj.width = GetFloatVal("width", L);
	obj.height = GetFloatVal("height", L);
	obj.properties = std::move(GetProperties(L));
	return obj;
}

/*
* GetStringVal()
* 
* Gets and returns a string value from an luatable.
* 
* Params:
*		const std::string& key: The key of the table whose value you want. Must not be empty.
*		lua_State* L: The state the table is in. Must not be null.
*
* Returns: std::string
*		The value of Table[key]. The lua_State is left the same as it was when passed.
*
* Throws: LuaError if Table[key] does not return a string value.
*
* Notes:
*		The first value on the stack MUST be the table you want
*		BEFORE you call this function. The function does not check
*		to confirm that this is true. You should do so before the call.
*/
std::string GetStringVal(const std::string& key, lua_State* L)
{
	// STK: table --
	lua_pushstring(L, key.c_str());
	// STK: table -- string
	lua_rawget(L, 1);
	// STK: table -- string?
	if (!lua_isstring(L, -1))
	{
		lua_pop(L, 1);
		// STK: table --
		return 0;
		//throw(LuaError("Table object's " + key + " property did not return a string value.", "Not provided", __FILE__, __LINE__));
	}
	// STK: table -- string
	std::string val(lua_tostring(L, -1));
	lua_pop(L, 1);
	return std::move(val);
}
/*
* GetFloatVal()
* 
* Gets and returns a float value from an luatable.
* 
* Params:
*		const std::string& key: The key of the table whose value you want. Must not be empty.
*		lua_State* L: The state the table is in. Must not be null.
*
* Returns: float
*		The value of Table[key]. The lua_State is left the same as it was when passed.
*
* Throws: LuaError if Table[key] does not return a float value.
*
* Notes:
*		The first value on the stack MUST be the table you want
*		BEFORE you call this function. The function does not check
*		to confirm that this is true. You should do so before the call.
*/
float GetFloatVal(const std::string& key, lua_State* L)
{
	// STK: table --
	lua_pushstring(L, key.c_str());
	// STK: table -- string
	lua_rawget(L, 1);
	// STK: table -- number?
	if (!lua_isnumber(L, -1))
	{
		lua_pop(L, 1);
		// STK: table --
		return 0;
		//throw(LuaError("Table object's " + key + "property did not return a string value.", "Not provided", __FILE__, __LINE__));
	}
	// STK: table -- number
	float val(lua_tonumber(L, -1));
	lua_pop(L, 1);
	return val;
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
		throw(std::exception("Table has not 'properties' key."));
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
			throw(std::exception("A key in properties is a non string value."));
		else if(!lua_isstring(L, -1))
			throw(std::exception("A key in properties returned a non string value."));
		// STK: table2 table1 -- string string
		props[lua_tostring(L, -2)] = lua_tostring(L, -1);
		lua_pop(L, 1);

	}
	// STK: table2 table1 --
	lua_remove(L, 1);
	// STK: table1
	return std::move(props);
}