#include "Script.h"
#include <lua.hpp>
#include <sstream>
#include <assert.h>
#include "Utility.h"

namespace VE
{
	static int instances = 0;
	//bool LoadScript(CScript* script);
	void ProvideGlobal(lua_State* L, const char* key);

	CScript::CScript(const std::string& filename, lua_State* state, const std::string& scriptID)
		: m_scriptID(scriptID)
		, m_state(state)
		, m_loaded(false)
	{
		m_buffer = FileToBuffer(filename);

		if (m_scriptID.empty())
		{
			std::stringstream ss;
			ss << "Script_" << ++instances;
			m_scriptID = ss.str();
		}

		assert(m_state != nullptr);
	}

	CScript::~CScript(void)
	{

	}

	bool CScript::Push(void)
	{
		// STK: --
		lua_getfield(m_state, LUA_REGISTRYINDEX, m_scriptID.c_str());
		// STK: -- table?
		if (!lua_istable(m_state, -1))
		{
			// STK: -- unknown
			lua_pop(m_state, 1);
			// STK: --
			return false;
		}
		// STK: -- table
		return true;
	}

	void CScript::Load(void)
	{
		if (IsLoaded())
			Unload();
		if (m_buffer.empty())
			return;

		if (luaL_loadbuffer(m_state, m_buffer.data(), m_buffer.size(), nullptr))
		{
			const char* error = lua_tostring(m_state, -1);
			lua_pop(m_state, 1);
			return;
		}

		// STK: func
		lua_createtable(m_state, 0, 1);
		ProvideGlobal(m_state, "io");
		ProvideGlobal(m_state, "print");
		// STK: func table
		lua_pushvalue(m_state, -1);
		// STK: func table table
		lua_setfield(m_state, LUA_REGISTRYINDEX, m_scriptID.c_str());
		// STK: func table
		if (!lua_setfenv(m_state, -2))
			return;
		// STK: func
		lua_pcall(m_state, 0, 0, 0);
		// STK:

		m_loaded = true;
	}

	void CScript::Unload(void)
	{
		if (m_state)
			return;
		// STK:
		lua_pushnil(m_state);
		// STK: nil
		lua_setfield(m_state, LUA_REGISTRYINDEX, m_scriptID.c_str());
		// STK:
		m_loaded = false;
	}

	void CScript::Update(double dt)
	{
		if (!Push())
			return;
		// STK: table
		lua_getfield(m_state, -1, "Update");
		// STK: table func
		lua_pushnumber(m_state, dt);
		// STK: table func number
		lua_pcall(m_state, 1, 0, 0);
		// STK: table
		lua_pop(m_state, 1);
		// STK:
	}

	void CScript::Render(void)
	{
		if (!Push())
			return;
		// STK: table
		lua_getfield(m_state, -1, "Render");
		// STK: table func number
		lua_pcall(m_state, 0, 0, 0);
		// STK: table
		lua_pop(m_state, 1);
		// STK:
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


