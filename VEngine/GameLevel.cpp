#include "GameLevel.h"
#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include "GameLevel.h"
#include "GameMap.h"
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

	CGameLevel::CGameLevel(CErrorLogger* logger, CEngine* engine)
		: IProcess(engine)
		, m_player(nullptr)
		, m_playerController(nullptr)
		, m_renderer(nullptr)
		, m_physics(nullptr)
		, m_playerView(nullptr)
		, m_gameMap(nullptr)
		, m_scriptEnv(nullptr)
		, m_logger(logger)
	{
		assert(GAMELEVEL == nullptr);
		GAMELEVEL = this;

		assert(engine != nullptr);
		assert(m_logger != nullptr);

		m_renderer = new CRender;
		m_physics = new CPhysics(Renderer()->Cam());
		m_gameMap = new CGameMap;
		m_playerController = new CPlayerController(nullptr);
		m_playerView = new CPlayerView(m_renderer);

		m_renderer->SetMapFile(m_gameMap);
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

		delete m_gameMap;
		m_gameMap = nullptr;

		delete m_renderer;
		m_renderer = nullptr;

		// No need to close the state. We don't own it.
		m_scriptEnv = nullptr;
		
		GAMELEVEL = nullptr;

	}

	void CGameLevel::Think(double dt)
	{
		if (m_mainScript.is_valid())
			luabind::call_member<void>(m_mainScript, "Update", dt);

		m_physics->Simulate();

		if (m_playerController)
			m_playerController->Update(dt);

		for (auto iter = m_animations.begin(); iter != m_animations.end(); ++iter)
			(*iter)->Logic(dt);
		for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
			(*iter)->Update(dt);
	}

	void CGameLevel::HandleEvent(const ALLEGRO_EVENT& ev)
	{
		if (GetPlayerController())
			GetPlayerController()->HandleEvent(ev);
	}

	void CGameLevel::Render(void)
	{
		if (Renderer())
			Renderer()->Render();
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
		if (m_scriptEnv == m_mainScript.interpreter())
			m_mainScript = luabind::object();
		m_scriptEnv = L;
	}

	CPlayer* CGameLevel::GetPlayer(void) const
	{
		return m_playerController->GetPlayer();
	}

	void CGameLevel::LoadMap(const std::string& filename)
	{
		if(!DoFile(m_scriptEnv, filename))
			return;

		m_gameMap->Read(luabind::globals(m_scriptEnv)["map"]);
	}

	CGameLevel* GameLevel(void)
	{
		return GAMELEVEL;
	};
}