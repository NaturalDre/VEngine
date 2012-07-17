#include "Application.h"
#include "Engine.h"
#include "GameLevelController.h"
#include "GameLevel.h"
#include <physfs.h>
#include <allegro5\allegro_physfs.h>
#include "Bitmap.h"
#include "LuabindExport.h"
#include <lua.hpp>
#include <luabind\luabind.hpp>

namespace VE
{
	CApplication::CApplication(void)
		: m_engine(nullptr)
		, m_controller(nullptr)
		, m_L(nullptr)
	{
		m_engine = new CEngine;
		m_controller = new CGameLevelController;

		m_L = lua_open();
		luaL_openlibs(m_L);
		luabind::open(m_L);

		m_engine->Init();
	}

	CApplication::~CApplication(void)
	{
		delete m_engine;
		m_engine = nullptr;
	}

	void CApplication::Init(void)
	{
		SetupDirectories();
		SetupScriptEnv();

		m_controller->GameLevel()->SetScriptEnv(m_L);
		m_engine->SetSystemController(m_controller);


	}

	void CApplication::SetupDirectories(void)
	{
		PHYSFS_addToSearchPath("Images.zip", 1);
		PHYSFS_addToSearchPath("Maps/Adventure", 1);
	}

	void CApplication::SetupScriptEnv(void)
	{
		ExportBindings(m_L);
		luaL_dofile(m_L, "Scripts/map/TiledLib.lua");
		luaL_dofile(m_L, "Scripts/game/vars.lua");
		luaL_dofile(m_L, "Scripts/game/common.lua");
		luaL_dofile(m_L, "Scripts/BadScript.lua");
		luaL_dofile(m_L, "Scripts/game/main.lua");
		luaL_dofile(m_L, "Maps/Adventure/Adventure.lua");



	}

	int CApplication::Run(void)
	{
		Init();
		m_controller->GameLevel()->LoadMap("Maps/Adventure/Adventure.lua");
		return m_engine->Run();
	}
}