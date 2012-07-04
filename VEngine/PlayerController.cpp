#include "PlayerController.h"
#include "Player.h"
#include "PlayerView.h"
#include <assert.h>
#include <allegro5\allegro5.h>
#include "Weapon.h"

namespace VE
{
	CPlayerController::CPlayerController(CPlayer* player)
		: m_player(player)
		, m_movedLThisFrame(false)
		, m_movedRThisFrame(false)
		, m_movedUpThisFrame(false)
		, m_movedDownThisFrame(false)
	{
		m_keys.resize(ALLEGRO_KEY_MAX, false);
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
		{
			m_keys[ev.keyboard.keycode] = true;
			HandleKeyDown(ev);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			m_keys[ev.keyboard.keycode] = false;
			HandleKeyUp(ev);
		}
		//if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_D)
		//	m_player->MoveRight();
	}

	void CPlayerController::HandleKeyDown(const ALLEGRO_EVENT& ev)
	{


		//if (ev.keyboard.keycode == ALLEGRO_KEY_D && !m_movedRThisFrame)
		//{
		//	if (IsKeyDown(ALLEGRO_KEY_A))
		//		m_player->SetXSpeed(0);
		//	else
		//	{
		//		m_player->SetXSpeed(5);
		//		m_player->SetDirection(e_Right);
		//		//m_keys[ALLEGRO_KEY_D] = true;
		//		m_movedRThisFrame = true;
		//	}
		//}
		//else if (ev.keyboard.keycode == ALLEGRO_KEY_A && !m_movedLThisFrame)
		//{
		//	if (IsKeyDown(ALLEGRO_KEY_D))
		//		m_player->SetXSpeed(0);
		//	else
		//	{
		//		m_player->SetXSpeed(-5);
		//		m_player->SetDirection(e_Left);
		//		//m_keys[ALLEGRO_KEY_D] = true;
		//		m_movedLThisFrame = true;
		//	}
		//}
		//else if (ev.keyboard.keycode == ALLEGRO_KEY_W && !m_movedUpThisFrame)
		//{
		//	if (IsKeyDown(ALLEGRO_KEY_S))
		//		m_player->SetYSpeed(0);
		//	else
		//	{
		//		m_player->SetYSpeed(-5);
		//		m_player->SetDirection(e_Up);
		//		//m_keys[ALLEGRO_KEY_W] = true;
		//		m_movedUpThisFrame = true;
		//	}
		//}
		//else if (ev.keyboard.keycode == ALLEGRO_KEY_S && !m_movedDownThisFrame)
		//{
		//	if (IsKeyDown(ALLEGRO_KEY_W))
		//		m_player->SetYSpeed(0);
		//	else
		//	{
		//		m_player->SetYSpeed(5);
		//		m_player->SetDirection(e_Down);
		//		//m_keys[ALLEGRO_KEY_S] = true;
		//		m_movedDownThisFrame = true;
		//	}
		//}
		//else if (ev.keyboard.keycode == ALLEGRO_KEY_F && m_player->GetCurrentWeapon())
		//	m_player->GetCurrentWeapon()->Fire(e_Right);
	}

	void CPlayerController::HandleKeyUp(const ALLEGRO_EVENT& ev)
	{
		//if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_A)
		//{
		//	m_player->SetXSpeed(0);
		//	//if (ev.keyboard.keycode == ALL

		//}
		//else if (ev.keyboard.keycode == ALLEGRO_KEY_W || ev.keyboard.keycode == ALLEGRO_KEY_S)
		//	m_player->SetYSpeed(0);


	}

	void CPlayerController::ProcessKeys(void)
	{
		const Direction dir = m_player->GetDirection();
		Direction tDir = dir;

		m_player->SetSpeed(b2Vec2(0,0));
		if (IsKeyDown(ALLEGRO_KEY_D) && !IsKeyDown(ALLEGRO_KEY_A))
		{
			m_player->SetXSpeed(5);
			tDir = e_Right;
			//m_player->SetDirection(e_Right);
		}
		else if (IsKeyDown(ALLEGRO_KEY_A) && !IsKeyDown(ALLEGRO_KEY_D))
		{
			m_player->SetXSpeed(-5);
			tDir = e_Left;
			//m_player->SetDirection(e_Left);
		}
		if (IsKeyDown(ALLEGRO_KEY_W) && !IsKeyDown(ALLEGRO_KEY_S))
		{
			m_player->SetYSpeed(-5);
			tDir = e_Up;
			//m_player->SetDirection(e_Up);
		}
		else if (IsKeyDown(ALLEGRO_KEY_S) && !IsKeyDown(ALLEGRO_KEY_W))
		{
			m_player->SetYSpeed(5);
			tDir = e_Down;
			//m_player->SetDirection(e_Down);
		}
		m_player->SetDirection(tDir);

		if (IsKeyDown(ALLEGRO_KEY_F))
			m_player->GetCurrentWeapon()->Fire(m_player->GetDirection());
	}

	void CPlayerController::Update(double deltaTime)
	{
		m_movedLThisFrame = false;
		m_movedRThisFrame = false;
		m_movedUpThisFrame = false;
		m_movedDownThisFrame = false;

		if (!m_player)
			return;

		ProcessKeys();
		m_player->Update(deltaTime);
	}

	void CPlayerController::SetPlayer(CPlayer* player)
	{
		//if (m_player)
		//	m_player->SubscribeFromAll(this);
		m_player = player;
	}
}