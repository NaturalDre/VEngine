#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include <assert.h>
#include <allegro5\allegro5.h>

namespace VE
{
	CPlayerController::CPlayerController(CPlayer* player, CPlayerView* playerView)
		: m_player(player)
		, m_playerView(playerView)
		, m_movedLThisFrame(false)
		, m_movedRThisFrame(false)
	{
		assert(m_player != nullptr);
		assert(m_playerView != nullptr);

		m_playerView->SetPlayer(player);
	}

	CPlayerController::~CPlayerController(void)
	{
		delete m_player;
		m_player = nullptr;
	}

	void CPlayerController::HandleEvent(const ALLEGRO_EVENT& ev)
	{
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
		}
		//if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_D)
		//	m_player->MoveRight();
	}

	void CPlayerController::Update(double deltaTime)
	{
		m_movedLThisFrame = false;
		m_movedRThisFrame = false;
	}
}