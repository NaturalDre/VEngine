#include "vengine\Level\VengineLevelLoader.h"
#include <vengine\Utility.h>
#include <vengine\Character\Player.h>
#include <vengine\ObjectManager.h>
#include <vengine\Render\Render.h>
namespace VE
{
	namespace Script
	{
		namespace File
		{
			const char* LS_LEVELFUNCTIONS("Scripts/LuaLevelFunctions.lua");
		}
	}
	CVengineLevelLoader::~CVengineLevelLoader(void)
	{
		UnloadCurrentLevel();
	}

	void CVengineLevelLoader::LoadLevel(const std::string& filename)
	{
		try
		{
			UnloadCurrentLevel();
			m_currentLevel.reset(new CVengineLevel(filename));
			m_currentLevel->LoadData();
			GatherObjects(filename);
		}
		catch(std::exception& e)
		{
			Utility::ReportError(e.what());
			exit(EXIT_FAILURE);
		}
	}

	void CVengineLevelLoader::UnloadCurrentLevel(void)
	{
		m_currentLevel.reset();
		//GetObjMgr().SetPlayer(nullptr);
		//GetRenderMgr().GetCam()->SetTarget(nullptr);
	}

	void CVengineLevelLoader::Logic(void)
	{

	}

	void CVengineLevelLoader::LoadFiles(const std::string& filename, lua_State* L)
	{
		if (!Utility::L_BufferAndLoad(filename, L))
			throw(std::exception(("Could not load: " + filename).c_str()));
		if (!Utility::L_BufferAndLoad(Script::File::LS_LEVELFUNCTIONS, L))
			throw(std::exception(("Could not load: " + std::string(Script::File::LS_LEVELFUNCTIONS)).c_str()));
	}

	void CVengineLevelLoader::GatherObjects(const std::string& filename)
	{
		lua_State* L = lua_open();
		luaL_openlibs(L);
		// Load level file into state.
		LoadFiles(filename, L);
		// Register factory functions inside FactoryTable
		RegisterFactories(L);
		// TO DO: Iterate through all objectlayers in level file and call
		// the appropriate factory function if available.

		lua_close(L);
		L = nullptr;
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

	void CVengineLevelLoader::RegisterFactories(lua_State* L)
	{
		AddFactoryFunc("Player", CPlayer::L_Create, L);
		AddFactoryFunc("SolidGround", Utility::CreateSolidGround, L);


		luaL_dostring(L, "FindObjects()");
		//lua_getglobal(L, "FactoryTable");
		//if (!lua_istable(L, -1))
		//	throw(std::exception("Factory table is not a table."));
		//lua_insert(L, 1);
		//lua_pushstring(L, "Box");
		//lua_pushcfunction(L,C Box::Create);
		//lua_rawset(L, 1);
	}



}