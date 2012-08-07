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

	CScript::CScript(const luabind::adl::object& scriptObject)
	{
		if (!scriptObject.is_valid() || luabind::type(scriptObject) != LUA_TUSERDATA)
			return;
		m_self = scriptObject;
	}

	CScript::~CScript(void)
	{
		m_self = luabind::object();
	}

	void CScript::Update(double dt)
	{
		luabind::call_member<void>(GetSelf(), "OnUpdate", dt);
	}

	//void CScript::Render(void)
	//{

	//}

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