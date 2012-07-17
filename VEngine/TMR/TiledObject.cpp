#include "TiledObject.h"
#include <lua.hpp>
#include "TiledLua.h"
#include <luabind\luabind.hpp>

using namespace Tiled;

TiledObject::TiledObject(TiledObject&& rhs)
	: m_name(rhs.m_name)
	, m_type(rhs.m_type)
	, m_x(rhs.m_x)
	, m_y(rhs.m_y)
	, m_width(rhs.m_width)
	, m_height(rhs.m_height)
	, m_properties(std::move(rhs.m_properties))
	, m_isValid(rhs.IsValid()) { }

TiledObject::TiledObject(const luabind::adl::object& data)
	: m_x(0)
	, m_y(0)
	, m_width(0)
	, m_height(0)
	, m_isValid(false)
{
	if (luabind::type(data) != LUA_TTABLE)
		return;

	try
	{
		m_name = luabind::object_cast<std::string>(data["name"]);
		m_type = luabind::object_cast<std::string>(data["type"]);
		m_x = luabind::object_cast<float>(data["x"]);
		m_y = luabind::object_cast<float>(data["y"]);
		m_width = luabind::object_cast<float>(data["width"]);
		m_height = luabind::object_cast<float>(data["height"]);	

		// STK: --
		data.push(data.interpreter());
		// STK: -- table
		auto t = data.interpreter();
		m_properties = GetProperties(data.interpreter());
		// STK: -- table
		lua_pop(data.interpreter(), 1);
		// STK: --
		m_isValid = true;
	}
	catch(...)
	{

	}
}

TiledObject TiledObject::CreateFromLua(lua_State* L)
{
	try
	{
		luabind::object data(luabind::from_stack(L, -1));
		if (luabind::type(data) != LUA_TTABLE)
			throw(std::exception("Variable passed to TiledObject::CreateFromLua is not a table."));

		TiledObject obj;
		obj.m_name = luabind::object_cast<std::string>(data["name"]);
		obj.m_type = luabind::object_cast<std::string>(data["type"]);
		obj.m_x = luabind::object_cast<float>(data["x"]);
		obj.m_y = luabind::object_cast<float>(data["y"]);
		obj.m_width = luabind::object_cast<float>(data["width"]);
		obj.m_height = luabind::object_cast<float>(data["height"]);

		for(luabind::iterator iter = luabind::iterator(data["properties"]), end; iter != end; ++iter)
		{
			obj.m_properties.insert(std::pair<const std::string, const std::string>
				(luabind::object_cast<const std::string>(iter.key())
				, luabind::object_cast<std::string>(*iter)));
		}

		return obj;
	}
	catch (...) { return TiledObject(); }
}