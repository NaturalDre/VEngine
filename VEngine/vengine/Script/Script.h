#ifndef SCRIPT_H
#define SCRIPT_H

#include <vengine\Script\LuaScript.h>
#include <lua.hpp>
#include <list>

namespace VE
{
	//struct ToLuaImporter
	//{
	//	void operator()(lua_State* L);
	//};

	class CScriptManager
	{
		friend CScriptManager& GetScriptMgr(void);
	protected:
		void LoadVLibs(void);
		void UpdateScripts(void);
	public:
		~CScriptManager(void);
		void DeregisterScript(CLuaScript* script);
		CLuaScript* LoadScript(const std::string& filename);
		lua_State* GetState(void) { return m_L; }
		void Logic(void);

		void BindToLua(void(*func)(lua_State* L));
		void SetProvideGlobals(void(*func)(lua_State* L)) { m_GiveGlobals = func; }
		//void ProvideGlobalsForScript(void (*func)(lua_State* L));
	private:
		CScriptManager(void);
		CScriptManager(CScriptManager const&);
		void operator=(CScriptManager const&);

		lua_State* m_L;
		void(*m_GiveGlobals)(lua_State* L);
		std::list<CLuaScript*> m_registeredScripts;

	};

	CScriptManager& GetScriptMgr(void);
}
#endif