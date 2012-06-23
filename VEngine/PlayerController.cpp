#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include <assert.h>
#include <allegro5\allegro5.h>

namespace VE
{
	CPlayerController::CPlayerController(CPlayer* player)
		: m_player(player)
		, m_movedLThisFrame(false)
		, m_movedRThisFrame(false)
	{
		//assert(m_player != nullptr);
		//assert(m_playerView != nullptr);

		//m_playerView->SetPlayer(player);
	}

	CPlayerController::~CPlayerController(void)
	{
		//delete m_player;
		m_player = nullptr;
	}

	void CPlayerController::HandleEvent(const ALLEGRO_EVENT& ev)
	{
		if (!m_player)
			return;

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_D && !m_movedRThisFrame)
			{
				m_player->MoveRight();
				m_movedRThisFrame = true;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A && !m_movedLThisFrame)
			{
				m_player->MoveLeft();
				m_movedLThisFrame = true;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_L)
				m_player->AdvanceLevel();
		}
		//if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_D)
		//	m_player->MoveRight();
	}

	void CPlayerController::Update(double deltaTime)
	{
		m_movedLThisFrame = false;
		m_movedRThisFrame = false;

		if (!m_player)
			return;
		m_player->Update(deltaTime);
	}

	void CPlayerController::SetPlayer(CPlayer* player)
	{
		//if (m_player)
		//	m_player->SubscribeFromAll(this);
		m_player = player;
	}
}