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
		, m_renderer(nullptr)
	{
		m_renderer = new CRender;
		m_gameLevel = new CGameLevel(m_renderer);
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
			m_gameLevel->Player()->HandleEvent(ev);
	}

	void CGameLevelController::Update(double deltaTime)
	{
		if (!m_gameLevel)
			return;

		//if (m_gameLevel->Player())
		//m_gameLevel->Player()->
		m_gameLevel->UpdateAll(deltaTime);
	}

	void CGameLevelController::Render(void)
	{
		m_renderer->Render();
	}

}