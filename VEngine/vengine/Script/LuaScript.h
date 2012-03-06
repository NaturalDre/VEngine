#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <lua.hpp>
#include <tolua++.h>
namespace VE
{
	class CScriptManager;
	class CLuaScript
	{
		friend CScriptManager;
	protected:

	public:
		virtual ~CLuaScript(void);

		/*
		 *	CallUpdate(void);
		 *
		 *	Calls the script's OnUpdate function if it has one.
		 *
		 *	Throws:
		 *		std::exception: If when CallUpdate calls L_GetFunction and this script's
		 *						scriptID is not a valid key in the global table. (Which is
		 *						where this script's environment resides(the key))
		 */
		void CallUpdate(void);
		/*
		 *	L_GetFunction()
		 *
		 *	Searches this scripts environment for a function of the specified name and
		 *	puts it at the top of the stack.
		 *
		 *
		 *	Params:
		 *		lua_State* L: The lua state where the script resides.
		 *		const char* scriptID: The script's key in LUA_GLOBALINDEX table.
		 *		const char* function: The function you want.
		 */
		static bool L_GetFunction(lua_State* L, const char* scriptID, const char* function);
	private:
		/*
		 *	CLuaScript()
		 *
		 *	Constructor.
		 *
		 *	Params:
		 *		const std::string& scriptID - The ID of for this script.
		 *
		 *	Notes:
		 *		The ID can not be changed. It is constant.
		 *		The ID is used as the key in the LUA_GLOBALINDEX table.
		 */
		CLuaScript(const std::string& scriptID);

		// This script's ID.
		const std::string m_scriptID;
	};

	class LuaError: public std::exception
	{
	public:
		const char* what() const throw();
		LuaError( const std::string& msg, const std::string& lfile = "Not provided", const std::string& cfile = "Not provided", size_t cline = 0);

		std::string luafile;
		std::string cppfile;

	private:
		const std::string error;
	};
}

#endif