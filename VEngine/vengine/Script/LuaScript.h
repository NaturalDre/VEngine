#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <lua.hpp>

namespace VE
{
	class CLuaScript
	{
	protected:
		static bool GetTable(lua_State* L, const std::string& scriptID);

	public:
		virtual ~CLuaScript(void);
		static CLuaScript* Create(const std::string& filename);

		void CallUpdate(void);
	private:
		CLuaScript(const std::string& filename);

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