#include "PlayerView.h"
#include "Player.h"
#include <iostream>
#include <allegro5\allegro5.h>
#include "PlayerEvents.h"
#include "Weapon.h"

namespace VE
{
	CPlayerView::CPlayerView(CRender* render)
		: IView(render)
		, m_player(nullptr)
	{
		m_anims.SetSpriteSheet("Images/player.png", 4, 3, 5); 
		m_anims.AddFrameSequence(FrameSequence(1, 3), "WalkDown");
		m_anims.AddFrameSequence(FrameSequence(4, 6), "WalkLeft");
		m_anims.AddFrameSequence(FrameSequence(10, 12), "WalkUp");
		m_anims.AddFrameSequence(FrameSequence(7, 9), "WalkRight");
	}

	CPlayerView::~CPlayerView(void)
	{
		if (m_player)
			m_player->SubscribeFromAll(this);
		m_player = nullptr;
	}

	void CPlayerView::Draw(void)
	{
		if (!m_player)
			return;

		VE::DrawBitmap(m_anims.GetCurrentAnim().GetFrame(), m_player->Position(), b2Vec2(0,0));
		m_player->GetCurrentWeapon()->Render();
	}

	void CPlayerView::Notify(int eventType)
	{
		if (eventType == ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C'))
			ChangeDirection(m_player->GetDirection());
	}

	void CPlayerView::ChangeDirection(DIRECTION dir)
	{
			if (dir == RIGHT)
				m_anims.SetCurrentAnim("WalkRight");
			else if (dir == LEFT)
				m_anims.SetCurrentAnim("WalkLeft");
			else if (dir == UP)
				m_anims.SetCurrentAnim("WalkUp");
			else if (dir == DOWN)
				m_anims.SetCurrentAnim("WalkDown");
	}

	void CPlayerView::SetPlayer(CPlayer* player)
	{
		if (m_player)
			m_player->SubscribeFromAll(this);

		m_player = player;

		if (m_player)
		{
			ChangeDirection(m_player->GetDirection());
			m_player->SubscribeTo("LevelUp", this);
			m_player->SubscribeTo("DirectionChanged", this);
		}
	}
}