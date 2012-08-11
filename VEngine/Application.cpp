#include "Application.h"
#include "Engine.h"
#include "GameLevel.h"
#include <physfs.h>
#include <allegro5\allegro_physfs.h>
#include "Bitmap.h"
#include "LuabindExport.h"
#include "Utility.h"
#include <lua.hpp>
#include <luabind\luabind.hpp>

namespace VE
{
	CApplication::CApplication(void)
		: m_engine(nullptr)
		, m_L(nullptr)
		, m_gameLevel(nullptr)
	{
		srand(time(nullptr));

		m_engine = new CEngine;
		m_engine->Init();

		m_L = lua_open();
		luaL_openlibs(m_L);
		luabind::open(m_L);

	}

	CApplication::~CApplication(void)
	{
		m_gameLevel->SetScriptEnv(nullptr);

		// The player must be freed before the state is closed, because
		// the player may own a valid script.
		// TO DO: Free all entities before closing the state.
		m_gameLevel->RemovePlayer();
		// The lua state needs to be closed before the controller,
		// because the state may own some objects who depend
		// on pointers owned by the controller. 
		lua_close(m_L);
		m_L = nullptr;

		delete m_gameLevel;
		m_gameLevel = nullptr;

		delete m_engine;
		m_engine = nullptr;
	}

	void CApplication::Init(void)
	{
		SetupDirectories();
		// CGameLevel needs certain directories 
		// set up before it's created, otherwise it will 
		// crash the program.
		m_gameLevel = new CGameLevel(&m_errorLogger, m_engine);	
		
		SetupScriptEnv();
		m_gameLevel->SetScriptEnv(m_L);

		m_engine->SetCallback(m_gameLevel);
	}

	void CApplication::SetupDirectories(void)
	{
		PHYSFS_addToSearchPath("Data", 1);
		PHYSFS_addToSearchPath("Data.zip", 1);
	}

	void CApplication::SetupScriptEnv(void)
	{
		ExportBindings(m_L);

		luabind::settable(luabind::globals(m_L), "Game", m_gameLevel);
		luabind::settable(luabind::globals(m_L), "Logger", &m_errorLogger);

		DoFile(m_L, "Scripts/game/app.lua");
		DoFile(m_L, "Scripts/map/TiledLib.lua");
		DoFile(m_L, "Scripts/game/vars.lua");
		DoFile(m_L, "Scripts/game/common.lua");
		DoFile(m_L, "Scripts/BadScript.lua");
		DoFile(m_L, "Scripts/game/main.lua");
		DoFile(m_L, "Scripts/game/playerscript.lua");
		DoFile(m_L, "Maps/Adventure/Adventure.lua");
		DoFile(m_L, "Scripts/game/weapons/ak_47.lua");




	}

	int CApplication::Run(void)
	{
		Init();
		try 
		{ 
			luabind::call_function<void>(m_L, "OnAppStartup");
			if (m_gameLevel->GetMainScript())
				luabind::call_member<void>(m_gameLevel->GetMainScript(), "StartUp");
		}
		catch(const luabind::error& e)
		{
			m_errorLogger.LogError(std::string("Attempt to call OnAppStartup generated error: ") + lua_tostring(m_L, -1));
			lua_pop(e.state(), 1);
		}

		return m_engine->Run();
	}
}