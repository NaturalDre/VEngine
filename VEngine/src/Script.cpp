#include <vengine\Script\Script.h>
#include <vengine\Utility.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>

namespace VE
{

	namespace Script
	{
		namespace File
		{
			const std::string LS_CLASS("Scripts/VLib/class.lua");
			const std::string LS_SCRIPT("Scripts/VLib/script.lua");
		}
	}

	CScriptManager::CScriptManager(void)
		: m_L(nullptr)
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
			if (!Utility::L_BufferAndLoad(Script::File::LS_SCRIPT, m_L))
			{
				const char* error = lua_tostring(m_L, -1);
				lua_pop(m_L, 1);
				throw(LuaError(Script::File::LS_SCRIPT, __FILE__, error, __LINE__));
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
		lua_getglobal(m_L, "SetupScript");
		// STK: func?
		if (!lua_isfunction(m_L, -1))
		{
			Utility::ReportError("SetupScript is not an function.", filename);
			exit(EXIT_FAILURE);
		}
		// STK: func
		lua_pushstring(m_L, scriptID.c_str());
		// STK: func string
		if (lua_pcall(m_L, 1, 1, 0))
		{
			const char* error = lua_tostring(m_L, -1);
			lua_pop(m_L, 1);
			Utility::ReportError(error, filename, __FILE__);
			exit(EXIT_FAILURE);
		}
		// STK: table?
		if (!lua_istable(m_L, -1))
			abort();
		// STK: table
		lua_setglobal(m_L, "env");
		// STK: 
		Utility::L_BufferAndLoad(filename, m_L);
		// STK:
		lua_pushnil(m_L);
		lua_setglobal(m_L, "env");

		CLuaScript* script(CLuaScript::Create(scriptID));

		m_registeredScripts.push_back(script);
		return script;
	}

	CScriptManager& GetScriptMgr(void)
	{
		static CScriptManager instance;
		return instance;
	}
}