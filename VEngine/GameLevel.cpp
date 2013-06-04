#include "GameLevel.h"
#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include "GameLevel.h"
#include "GameMap.h"
#include "Render.h"
#include <lua.hpp>
#include <lauxlib.h>
#include <luabind\luabind.hpp>
#include "Script.h"
#include "Utility.h"
#include "Locator.h"

namespace VE
{
	CGameLevel* GAMELEVEL(nullptr);

	CGameLevel::CGameLevel(CEngine* engine)
		: IProcess(engine)
		, m_player(nullptr)
		, m_playerController(nullptr)
		, m_playerView(nullptr)
		, m_gameMap(nullptr)
		, m_scriptEnv(nullptr)
		, m_engine(engine)
	{
		assert(GAMELEVEL == nullptr);
		GAMELEVEL = this;

		assert(m_engine != nullptr);
		assert(m_logger != nullptr);

		m_gameMap = new CGameMap(this);
	}

	CGameLevel::~CGameLevel(void)
	{
		RemovePlayer();

		delete m_playerController;
		m_playerController = nullptr;

		delete m_playerView;
		m_playerView = nullptr;

		delete m_gameMap;
		m_gameMap = nullptr;

		// No need to close the state. We don't own it.
		m_scriptEnv = nullptr;
		
		GAMELEVEL = nullptr;

	}

	void CGameLevel::Think(double dt)
	{
		FreeMarkedEntities();
		if (!GetEngine()->IsLogicPaused())
		{
			if (m_mainScript.is_valid())
				luabind::call_member<void>(m_mainScript, "Update", dt);

			if (m_playerController)
				m_playerController->Update(dt);

			for (auto iter = m_animations.begin(); iter != m_animations.end(); ++iter)
				(*iter)->Logic(dt);
			for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
				(*iter)->Update(dt);
		}
	}

	void CGameLevel::FreeMarkedEntities(void)
	{
		for (auto iter = m_entitiesToDelete.begin(); iter != m_entitiesToDelete.end(); ++iter)
		{
			IEntity* entity = *iter;
			delete entity;
		}
		m_entitiesToDelete.clear();
	}

	void CGameLevel::AddPlayer(void)
	{
		if (!m_gameMap->IsValid())
			return;
		if (m_player)
		{
			delete m_player;
			m_player = nullptr;
		}

		if (m_playerController)
		{
			delete m_playerController;
			m_playerController = nullptr;
		}

		if (m_playerView)
		{
			delete m_playerView;
			m_playerView = nullptr;
		}

		m_player = CreatePlayer(this, m_gameMap->GetPlayerSpawn());
		m_playerController = new CPlayerController(m_player);
		m_playerView = new CPlayerView();
		m_playerView->SetPlayer(m_player);
		CLocator::GetRenderer()->GetCamera()->Watch(m_player);
	}

	void CGameLevel::RemovePlayer(void)
	{
		CLocator::GetRenderer()->GetCamera()->Watch(nullptr);
		if (m_playerView)
			m_playerView->SetPlayer(nullptr);
		if (m_playerController)
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
		m_gameMap->Reset();
		bool success = m_gameMap->Read(filename);


		// Don't run any game logic or physics if the map does not load.
		GetEngine()->SetPauseLogic(!success);
		GetEngine()->SetPausePhysics(!success);
	}

	void CGameLevel::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<CGameLevel>("CGameLevel")
				//.property("renderer", &CGameLevel::GetRenderer)
				.property("physics", &CGameLevel::GetPhysics)
				.property("map", &CGameLevel::GetMap)
				.property("logger", &CGameLevel::GetLogger)
				.property("player", &CGameLevel::GetPlayer)
				.def("LoadMap", &CGameLevel::LoadMap)
				.def("AddPlayer", &CGameLevel::AddPlayer)
				.def("RemovePlayer", &CGameLevel::RemovePlayer)
				.def("SetMainScript", &CGameLevel::SetMainScript)
			];
	}

	CGameLevel* GameLevel(void)
	{
		return GAMELEVEL;
	};
}