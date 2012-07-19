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
		: m_player(nullptr)
		, m_playerController(nullptr)
		, m_renderer(nullptr)
		, m_physics(nullptr)
		, m_playerView(nullptr)
		, m_mapFile(nullptr)
		, m_scriptEnv(nullptr)
	{
		assert(GAMELEVEL == nullptr);
		GAMELEVEL = this;

		m_renderer = new CRender;
		m_physics = new CPhysics(Renderer()->Cam());
		m_mapFile = new Tiled::CMapFile;
		m_playerController = new CPlayerController(nullptr);
		m_playerView = new CPlayerView(m_renderer);

		m_renderer->SetMapFile(m_mapFile);
		m_renderer->SetPhysics(m_physics);
	}

	CGameLevel::~CGameLevel(void)
	{
		RemovePlayer();

		delete m_playerController;
		m_playerController = nullptr;

		delete m_playerView;
		m_playerView = nullptr;

		delete m_physics;
		m_physics = nullptr;

		delete m_mapFile;
		m_mapFile = nullptr;

		delete m_renderer;
		m_renderer = nullptr;

		// No need to close the state. We don't own it.
		m_scriptEnv = nullptr;
		
		GAMELEVEL = nullptr;

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

	void CGameLevel::AddPlayer(void)
	{
		if (m_player)
			delete m_player;

		m_player = CreatePlayer(this);

		m_playerController->SetPlayer(m_player);
		m_playerView->SetPlayer(m_player);
		m_renderer->Cam()->Watch(m_player);
	}

	void CGameLevel::RemovePlayer(void)
	{
		m_renderer->Cam()->Watch(nullptr);
		m_playerView->SetPlayer(nullptr);
		m_playerController->SetPlayer(nullptr);

		delete m_player;
		m_player = nullptr;	
	}

	void CGameLevel::SetScriptEnv(lua_State* L)
	{
		if (m_scriptEnv)
			lua_close(m_scriptEnv);
		m_scriptEnv = L;
	}

	CPlayer* CGameLevel::GetPlayer(void) const
	{
		return m_playerController->GetPlayer();
	}

	void CGameLevel::LoadMap(const std::string& filename)
	{
		m_mapFile->ReadMapFile(filename);
		//m_player = CreatePlayer(this);
		//m_playerView = new CPlayerView(Renderer());
		//m_playerController = new CPlayerController(m_player);

		//m_playerView->SetPlayer(m_player);
		//m_playerController->SetPlayer(m_player);
		//m_renderer->Cam()->Watch(m_player);

		//luaL_dostring(m_scriptEnv, "Main = Main(); Main:StartUp();");
		//luabind::settable(luabind::globals(m_scriptEnv), "Game", this);
		//luaL_dostring(m_scriptEnv, "print(type(GameLevel)); print(Game:LevelName()); ");
	}

	CGameLevel* GameLevel(void)
	{
		return GAMELEVEL;
	};
}