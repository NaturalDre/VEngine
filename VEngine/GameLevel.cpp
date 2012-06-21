#include "GameLevel.h"
#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"

namespace VE
{
	CGameLevel::CGameLevel(CRender* renderer)
		: m_playerController(nullptr)
		, m_renderer(renderer)
	{
		m_playerController = new CPlayerController(new CPlayer, new CPlayerView(renderer));
	}

	CGameLevel::~CGameLevel(void)
	{
		delete m_playerController;
		m_playerController = nullptr;
	}

	void CGameLevel::UpdateAll(double deltaTime)
	{
		if (m_playerController)
			m_playerController->Update(deltaTime);

		for (auto iter = m_controllers.begin(); iter != m_controllers.end(); ++iter)
			(*iter)->Update(deltaTime);
	}
}