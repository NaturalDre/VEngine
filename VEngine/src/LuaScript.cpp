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

	bool CLuaScript::L_GetFunction(lua_State* L, const char* scriptID, const char* function)
	{
		// STK: --
		lua_getfield(L, LUA_REGISTRYINDEX, scriptID);
		// STK: -- table?
		if (!lua_istable(L, -1))
		{
			lua_pop(L, 1);
			throw(std::exception((std::string("L_GetFunction: The top object on the stack is not a table.\n") +  __FILE__ "\n" + scriptID).c_str()));
		}
		// STK: -- table
		lua_getfield(L, -1, function);
		// STK: -- function?
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}
		// STK: -- function
		return true;
	}
	CLuaScript::CLuaScript(const std::string& filename)
		: m_scriptID(filename)
	{

	}

	CLuaScript::~CLuaScript(void)
	{

	}

	void CLuaScript::CallUpdate(void)
	{
		lua_State* L = GetScriptMgr().GetState();
		if (L_GetFunction(L, m_scriptID.c_str(), Script::Var::OnUpdate.c_str()))
			lua_pcall(L, 0, 0, 0);
	}

	//CLuaScript* CLuaScript::Create(const std::string& scriptID)
	//{
	//	return new CLuaScript(scriptID);
	//}

	LuaError::LuaError(const std::string& msg, const std::string& lfile, const std::string& cfile,  size_t cline)
		: error(msg)
		, luafile(lfile)
		, cppfile(cfile)
	{

	}

	const char* LuaError::what() const throw()
	{
		return error.c_str();
	}
}