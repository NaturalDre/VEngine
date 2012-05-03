#include "vengine\Level\Level.h"
#include <vengine\ObjectManager.h>
#include <vengine\Render\Render.h>
#include <vengine\Character\Player.h>

namespace VE
{
	namespace Script
	{
		namespace File
		{
			const char* LS_LEVELFUNCTIONS("Scripts/LuaLevelFunctions.lua");
		}
	}

	//	// Helper function. Adds cfunction to the FactoryTable in lua
	//void AddFactoryFunc(const std::string& key, int(*f)(lua_State*), lua_State* L)
	//{
	//	lua_getglobal(L, "FactoryTable");
	//	// STK:  -- table?
	//	if (!lua_istable(L, -1))
	//		throw(std::exception("Factory table is not a table."));
	//	// STK: -- table
	//	lua_insert(L, 1);
	//	// STK: table --
	//	lua_pushstring(L, key.c_str());
	//	// STK: table -- string
	//	lua_pushcfunction(L, f);
	//	// table -- string cfunc
	//	lua_rawset(L, 1);
	//	// table --
	//	lua_remove(L, 1);
	//	// --
	//}

	CLevelManager::CLevelManager(void)
		: m_RegisterFactories(nullptr)
	{

	}

	void CLevelManager::Cleanup(void)
	{
		UnloadCurrentLevel();
	}

	void CLevelManager::Logic(void)
	{

	}

	void CLevelManager::LoadLevel(const std::string& filename)
	{
		try
		{
			UnloadCurrentLevel();
			m_currentLevel.reset(new CVengineLevel(filename));
			m_currentLevel->LoadData();
			CallFactories(filename);
		}
		catch(std::exception& e)
		{
			Utility::ReportError(e.what());
			exit(EXIT_FAILURE);
		}
	}

	void CLevelManager::UnloadCurrentLevel(void)
	{
		m_gameObjects.clear();
		m_bodies.clear();
		GetObjMgr().SetPlayer(nullptr);
		GetRenderMgr().GetCam()->SetTarget(nullptr);	
	}

	void CLevelManager::CallFactories(const std::string& filename)
	{
		lua_State* L = lua_open();
		luaL_openlibs(L);
		// Load level file into state.
		LoadFiles(filename, L);
		// Register factory functions inside FactoryTable
		if (m_RegisterFactories)
		{
			m_RegisterFactories(L);
			luaL_dostring(L, "FindObjects()");
		}
		lua_close(L);
		L = nullptr;
	}

	void CLevelManager::LoadFiles(const std::string& filename, lua_State* L)
	{
		if (!Utility::L_BufferAndLoad(filename, L))
			throw(std::exception(("Could not load: " + filename).c_str()));
		if (!Utility::L_BufferAndLoad(Script::File::LS_LEVELFUNCTIONS, L))
			throw(std::exception(("Could not load: " + std::string(Script::File::LS_LEVELFUNCTIONS)).c_str()));
	}

	void CLevelManager::SetLevelFactories(void(*func)(lua_State* L))
	{
		m_RegisterFactories = func;
	}

	CLevelManager& GetLvlMgr(void)
	{
		static CLevelManager instance;
		return instance;
	}
};