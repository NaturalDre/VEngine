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
		, m_movedUpThisFrame(false)
		, m_movedDownThisFrame(false)
	{

	}

	CPlayerController::~CPlayerController(void)
	{
		m_player = nullptr;
	}

	void CPlayerController::HandleEvent(const ALLEGRO_EVENT& ev)
	{
		if (!m_player)
			return;

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_CHAR)
			HandleKeyDown(ev);
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
			HandleKeyUp(ev);

		//if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_D)
		//	m_player->MoveRight();
	}

	void CPlayerController::HandleKeyDown(const ALLEGRO_EVENT& ev)
	{
		if (ev.keyboard.keycode == ALLEGRO_KEY_D && !m_movedRThisFrame)
		{
			m_player->SetXSpeed(5);
			m_movedRThisFrame = true;
		}
		else if (ev.keyboard.keycode == ALLEGRO_KEY_A && !m_movedLThisFrame)
		{
			m_player->SetXSpeed(-5);
			m_movedLThisFrame = true;
		}
		else if (ev.keyboard.keycode == ALLEGRO_KEY_W && !m_movedUpThisFrame)
		{
			m_player->SetYSpeed(-5);
			m_movedUpThisFrame = true;
		}
		else if (ev.keyboard.keycode == ALLEGRO_KEY_S && !m_movedDownThisFrame)
		{
			m_player->SetYSpeed(5);
			m_movedDownThisFrame = true;
		}
	}

	void CPlayerController::HandleKeyUp(const ALLEGRO_EVENT& ev)
	{
		if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_A)
			m_player->SetXSpeed(0);
		else if (ev.keyboard.keycode == ALLEGRO_KEY_W || ev.keyboard.keycode == ALLEGRO_KEY_S)
			m_player->SetYSpeed(0);
	}

	void CPlayerController::Update(double deltaTime)
	{
		m_movedLThisFrame = false;
		m_movedRThisFrame = false;
		m_movedUpThisFrame = false;
		m_movedDownThisFrame = false;

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