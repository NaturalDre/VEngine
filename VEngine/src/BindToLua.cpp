#include <vengine\BindToLua.h>
#include <lua.hpp>
#include <vengine\TLPP\tolua_Application.h>
#include <vengine\Application.h>

void ProvideGlobal(lua_State* L, void* value, const char* key, const char* type)
{
	// STK: table?
	if (!lua_istable(L, -1))
		throw(std::exception("Value at top of stack is not table. \nScript.cpp. \nProvideGlobal."));
	// STK: table
	tolua_pushusertype(L, value, type);
	// STK: table userdata
	lua_setfield(L, -2, key);
	// STK: table
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
}

void BindCPPToLua(lua_State* L)
{
	tolua_Application_open(L);


}

void ProvideGlobals(lua_State* L)
{
	ProvideGlobal(L, VE::GetApp(), "App", "CApplication");
	ProvideGlobal(L, "MAINMENU");
	ProvideGlobal(L, "GAMEPAUSED");
	ProvideGlobal(L, "GAMEINPROGRESS");
}

