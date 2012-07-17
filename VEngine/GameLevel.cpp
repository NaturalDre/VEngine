#include "GameLevel.h"
#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include "GameLevel.h"
#include "TMR\MapFile.h"
#include "Render.h"
#include "Barrel.h"
#include <lua.hpp>
#include <lauxlib.h>
#include <luabind\luabind.hpp>
#include "Script.h"
#include "Utility.h"

namespace VE
{
	CGameLevel* GAMELEVEL(nullptr);

	CGameLevel::CGameLevel(void)
		: m_playerController(nullptr)
		, m_renderer(nullptr)
		, m_physics(nullptr)
		, m_player(nullptr)
		, m_playerView(nullptr)
		, m_mapFile(nullptr)
		, m_scriptEnv(nullptr)
	{
		assert(GAMELEVEL == nullptr);
		GAMELEVEL = this;
	
		m_renderer = new CRender;
		m_physics = new CPhysics(Renderer()->Cam());
		m_mapFile = new Tiled::CMapFile;

		m_renderer->SetMapFile(m_mapFile);
		m_renderer->SetPhysics(m_physics);
		m_renderer->Cam()->Watch(m_player);

		Setup();
	}

	CGameLevel::~CGameLevel(void)
	{
		delete m_playerController;
		m_playerController = nullptr;

		delete m_playerView;
		m_playerView = nullptr;

		delete m_player;
		m_player = nullptr;

		delete m_physics;
		m_physics = nullptr;

		delete m_mapFile;
		m_mapFile = nullptr;

		delete m_renderer;
		m_renderer = nullptr;

		GAMELEVEL = nullptr;
	}

	void CGameLevel::Setup(void)
	{



		//m_player = CreatePlayer(this);
		//m_playerView = new CPlayerView(Renderer());
		//m_playerController = new CPlayerController(m_player);

		//m_playerView->SetPlayer(m_player);
		//m_playerController->SetPlayer(m_player);

		// Test: Will likely call ReadMapFile from somewhere else.
		//m_mapFile->ReadMapFile("Maps/Adventure/Adventure.lua");		
	}

	void CGameLevel::UpdateAll(double deltaTime)
	{
		if (m_scriptEnv)
			luaL_dostring(m_scriptEnv, "Main:Update()");
		m_physics->Simulate();

		if (m_playerController)
			m_playerController->Update(deltaTime);

		for (auto iter = m_animations.begin(); iter != m_animations.end(); ++iter)
			(*iter)->Logic(deltaTime);
		for (auto iter = m_controllers.begin(); iter != m_controllers.end(); ++iter)
			(*iter)->Update(deltaTime);
	}

	void CGameLevel::SetScriptEnv(lua_State* L)
	{
		if (m_scriptEnv)
			lua_close(m_scriptEnv);
		m_scriptEnv = L;
	}

	void CGameLevel::LoadMap(const std::string& filename)
	{
		m_mapFile->ReadMapFile(filename);
		m_player = CreatePlayer(this);
		m_playerView = new CPlayerView(Renderer());
		m_playerController = new CPlayerController(m_player);

		m_playerView->SetPlayer(m_player);
		m_playerController->SetPlayer(m_player);
		m_renderer->Cam()->Watch(m_player);

		luaL_dostring(m_scriptEnv, "Main = Main(); Main:StartUp();");



		//auto test = new CBarrel(this);
		//try
		//{
		//	auto s = new CScript(
		//		Call_Func(
		//		GetFactory(m_scriptEnv, "BadScript"), "Test"));
		//	luabind::call_member<void>(s->GetSelf(), "Talk2", "Pie");
		//	test->AddScript(s);
		//	luaL_dostring(m_scriptEnv, "LoadObjects(Objects);");
		//}

		//catch(const luabind::error& e)
		//{
		//	vError(lua_tostring(e.state(), -1));
		//	lua_pop(e.state(), -1);
		//}
		//catch(const luabind::cast_failed& e)
		//{
		//	auto t = e.what();
		//}
	}

	CGameLevel* GameLevel(void)
	{
		return GAMELEVEL;
	};
}