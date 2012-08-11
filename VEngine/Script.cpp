#include "Script.h"
#include <lua.hpp>
#include <sstream>
#include <assert.h>
#include "Utility.h"
#include <luabind\luabind.hpp>
#include <boost\lexical_cast.hpp>

using namespace luabind;

namespace VE
{
	void ProvideGlobal(lua_State* L, const char* key);

	luabind::object GetFactory(lua_State* L, const std::string& factory)
	{
		// STK: --
		lua_getglobal(L, factory.c_str());
		// STK: -- userdata?
		if (!lua_isuserdata(L, -1))
			return luabind::object();;
		// STK: -- userdata
		luabind::object func = luabind::object(luabind::from_stack(L, -1));
		lua_pop(L, 1);
		// STK: --
		return std::move(func);
	}

	CScript::CScript(lua_State* state, const std::string& scriptName)
	{
		// Load the script. Inside the lua_State should be different functions
		// for creating a script. This line will call that function with no parameters.
		m_self = luabind::call_function<luabind::object>(state, scriptName.c_str());
	}

	CScript::CScript(const luabind::adl::object& scriptObject)
	{
		// Make sure the object passed is valid and is either userdata or a table.
		if (!scriptObject.is_valid() || (luabind::type(scriptObject) != LUA_TUSERDATA || luabind::type(scriptObject) != LUA_TTABLE))
			return;
		m_self = scriptObject;
	}

	CScript::~CScript(void)
	{
		m_self = luabind::object();
	}

	void CScript::Update(double dt)
	{
		if (GetSelf().is_valid())
			luabind::call_member<void>(GetSelf(), "OnUpdate", dt);
	}

	void ProvideGlobal(lua_State* L, const char* key)
	{
		// STK: table?
		if (!lua_istable(L, -1))
			throw(std::exception("Value at top of stack is not table. \nScript.cpp. \nProvideGlobal."));
		// STK: table
		lua_getglobal(L, key);
		// STK: table value
		lua_setfield(L, -2, key);
		// STK: table
	}
}