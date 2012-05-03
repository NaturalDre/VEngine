#include <string>
#include <vengine\VengineStatics.h>
#include <vengine\TLPP\tolua_Application.h>

#include <vengine\Application.h>
#include <vengine\Character\Player.h>
#include <vengine\Gameplay\Bouncer.h>

using namespace VE;

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

// Helper function. Adds cfunction to the FactoryTable in lua
void AddFactoryFunc(const std::string& key, int(*f)(lua_State*), lua_State* L)
{
	lua_getglobal(L, "FactoryTable");
	// STK:  -- table?
	if (!lua_istable(L, -1))
		throw(std::exception("Factory table is not a table."));
	// STK: -- table
	lua_insert(L, 1);
	// STK: table --
	lua_pushstring(L, key.c_str());
	// STK: table -- string
	lua_pushcfunction(L, f);
	// table -- string cfunc
	lua_rawset(L, 1);
	// table --
	lua_remove(L, 1);
	// --
}

void ProvideLevelFactories(lua_State* L)
{
	AddFactoryFunc("Player", CPlayer::L_Create, L);
	AddFactoryFunc("SolidGround", Utility::CreateSolidGround, L);
	AddFactoryFunc("Bouncer", CBouncer::L_Create, L);
}