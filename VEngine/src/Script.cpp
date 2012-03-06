#include <vengine\Script\Script.h>
#include <vengine\Utility.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
#include <vengine\Application.h>

namespace VE
{

	namespace Script
	{
		namespace File
		{
			const std::string LS_CLASS("Scripts/VLib/class.lua");
		}
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

	void ProvideGlobals(lua_State* L)
	{
		ProvideGlobal(L, "print");
		ProvideGlobal(L, "io");
		//ProvideGlobal(L, "App");
	}

	CScriptManager::CScriptManager(void)
		: m_L(nullptr)
		, m_GiveGlobals(nullptr)
	{
		m_L = lua_open();
		luaL_openlibs(m_L);
		tolua_open(m_L);
		LoadVLibs();
	}

	CScriptManager::~CScriptManager(void)
	{
		lua_close(m_L);
		m_L = nullptr;
	}

	void CScriptManager::LoadVLibs(void)
	{
		try
		{
			if (!Utility::L_BufferAndLoad(Script::File::LS_CLASS, m_L))
			{
				const char* error = lua_tostring(m_L, -1);
				lua_pop(m_L, 1);
				throw(LuaError(Script::File::LS_CLASS, __FILE__, error, __LINE__));
			}
		}
		catch(LuaError& e)
		{
			Utility::ReportError(e.what(), "CScriptManager::LoadVLibs.");
			exit(EXIT_FAILURE);
		}
	}

	void CScriptManager::DeregisterScript(CLuaScript* script)
	{
		m_registeredScripts.remove(script);
	}

	void CScriptManager::UpdateScripts(void)
	{

	}

	CLuaScript* CScriptManager::LoadScript(const std::string& filename)
	{
		if (filename.empty())
			return nullptr;

		const std::string scriptID = Utility::StripFilename(filename);

		auto buffer = Utility::FileToBuffer(filename);
		if (luaL_loadbuffer(m_L, buffer.data(), buffer.size(), nullptr))
		{
			const char* error = lua_tostring(m_L, -1);
			lua_pop(m_L, -1);
			throw(std::exception(error));
		}

		// STK: func
		lua_createtable(m_L, 0, 1);
		// STK: func table
		ProvideGlobals(m_L);
		if (m_GiveGlobals)
			m_GiveGlobals(m_L);
		// STK: func table
		lua_pushvalue(m_L, -1);
		// STK: func table table
		lua_setfield(m_L, LUA_REGISTRYINDEX, scriptID.c_str());
		// STK: func table
		lua_setfenv(m_L, -2);
		// STK: func
		lua_pcall(m_L, 0, 0, 0);
		// STK:

		CLuaScript* script(new CLuaScript(scriptID));
		m_registeredScripts.push_back(script);
		return script;
	}

	void CScriptManager::BindToLua(void(*func)(lua_State*))
	{
		func(m_L);
	}

	//void CScriptManager::ProvideGlobalsForScript(void(*func)(lua_State* L))
	//{
	//	func(m_L);
	//}
	CScriptManager& GetScriptMgr(void)
	{
		static CScriptManager instance;
		return instance;
	}
}