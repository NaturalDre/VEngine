#include "vengine\Script\LuaScript.h"
#include <vengine\Script\Script.h>
#include <vengine\Utility.h>
#include <array>

namespace VE
{
	namespace Script
	{
		namespace Var
		{
			const std::string OnUpdate = "OnUpdate";
		}
	}
	CLuaScript::CLuaScript(const std::string& filename)
		: m_scriptID(filename)
	{

	}

	CLuaScript::~CLuaScript(void)
	{

	}

	bool CLuaScript::GetTable(lua_State* L, const std::string& scriptID)
	{
		lua_getglobal(L, "ScriptTable");
		// STK: -- table?
		if (!lua_istable(L, -1))
			return false;
		// STK: -- table
		lua_insert(L, 1);
		// STK: table --
		lua_pushstring(L, scriptID.c_str());
		// STK: table? -- string
		lua_rawget(L, 1);
		// STK: table -- table?
		if (!lua_istable(L, -1))
			return false;
		// STK: table -- table
		lua_remove(L, 1);
		// STK: -- table
		lua_insert(L, 1);
		// STK: table --
		return true;
	}

	void CLuaScript::CallUpdate(void)
	{
		lua_State* L = GetScriptMgr().GetState();

		if (GetTable(L, m_scriptID))
		{
			// STK: table --
			lua_pushstring(L, Script::Var::OnUpdate.c_str());
			// STK: table -- string
			lua_rawget(L, 1);
			// STK: table -- function?
			if(lua_pcall(L, 0, 0, 0))
			{
				const char* error = lua_tostring(L, -1);
				lua_pop(L, 1);
				Utility::ReportError(error, Script::Var::OnUpdate + " is not a function of this script.", m_scriptID);
			}
			// STK: table -- 
			lua_remove(L, 1);
			// STK: --
		}
	}

	CLuaScript* CLuaScript::Create(const std::string& scriptID)
	{
		return new CLuaScript(scriptID);
	}

	LuaError::LuaError(const std::string& msg, const std::string& lfile, const std::string& cfile,  size_t cline)
		: error(msg)
		, luafile(lfile)
		, cppfile(cfile)
	{
		//std::array<char, 4> v;
		//const char* line = itoa(cline, v.data(), 10);
		//error = (("Lua File: " + lfile + "\n" + msg + "\n\nCPP File: " + cfile + "\nCPP File Line: " + v.data()).c_str());
	}

	const char* LuaError::what() const throw()
	{
		//error = ("CPP File: " + cppfile + "\nLua File: " + luafile + "\nError: " + error);
		return error.c_str();
	}
}