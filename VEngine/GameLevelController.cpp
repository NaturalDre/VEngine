#include "GameLevelController.h"
#include "GameLevel.h"
#include "PlayerController.h"
#include "Player.h"
#include "Render.h"
#include <exception>

namespace VE
{
	CGameLevelController::CGameLevelController(void)
		: m_gameLevel(nullptr)
	{
		m_gameLevel = new CGameLevel;
	}		

	CGameLevelController::~CGameLevelController(void)
	{
		delete m_gameLevel;
		m_gameLevel = nullptr;
	}

	void CGameLevelController::Notify(IEvent* ev)
	{

	}

	void CGameLevelController::PushSystemEvent(ALLEGRO_EVENT& ev)
	{
		if (m_gameLevel)
			m_gameLevel->GetPlayerController()->HandleEvent(ev);
	}

	void CGameLevelController::Update(double deltaTime)
	{
		if (!m_gameLevel)
			return;

		m_gameLevel->UpdateAll(deltaTime);
	}

	void CGameLevelController::Render(void)
	{
		m_gameLevel->Renderer()->Render();
	}

}