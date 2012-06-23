#include "GameLevel.h"
#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include "GameLevel.h"
#include "TMR\MapFile.h"
#include "Render.h"

namespace VE
{
	CGameLevel::CGameLevel(CRender* renderer)
		: m_playerController(nullptr)
		, m_renderer(renderer)
		, m_physics(nullptr)
		, m_player(nullptr)
		, m_playerView(nullptr)
		, m_mapFile(nullptr)
	{
		m_mapFile = new Tiled::CMapFile;
		m_physics = new CPhysics;
		m_player = new CPlayer;
		m_playerView = new CPlayerView(Renderer());
		m_playerController = new CPlayerController(m_player);

		m_playerView->SetPlayer(m_player);
		m_playerController->SetPlayer(m_player);

		std::string err;
		// Test: will likely call ReadMapFile from somewhere else.
		m_mapFile->ReadMapFile("Simple.lua", err);

		m_renderer->SetMapFile(m_mapFile);
		m_renderer->SetCam(new CCamera);
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

		// We don't own it.
		m_renderer = nullptr;
	}

	void CGameLevel::UpdateAll(double deltaTime)
	{
		m_physics->Simulate();

		if (m_playerController)
			m_playerController->Update(deltaTime);

		for (auto iter = m_controllers.begin(); iter != m_controllers.end(); ++iter)
			(*iter)->Update(deltaTime);
	}
}