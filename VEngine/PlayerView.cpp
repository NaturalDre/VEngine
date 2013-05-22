#include "PlayerView.h"
#include "Player.h"
#include <iostream>
#include <allegro5\allegro5.h>
#include "PlayerEvents.h"

namespace VE
{
	CPlayerView::CPlayerView(CRender* render)
		: IView(render)
		, m_player(nullptr)
	{
		m_anims.SetSpriteSheet("Images/player.png", 4, 3, 5); 
		m_anims.AddFrameSequence(FrameSequence(1, 3), "Walk_Down");
		m_anims.AddFrameSequence(FrameSequence(4, 6), "Walk_Left");
		m_anims.AddFrameSequence(FrameSequence(10, 12), "Walk_Up");
		m_anims.AddFrameSequence(FrameSequence(7, 9), "Walk_Right");

		m_anims.AddFrameSequence(FrameSequence(1,1), "Idle_Down");
		m_anims.AddFrameSequence(FrameSequence(4,4), "Idle_Left");
		m_anims.AddFrameSequence(FrameSequence(10,10), "Idle_Up");
		m_anims.AddFrameSequence(FrameSequence(7, 7), "Idle_Right");
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

		VE::DrawBitmap(*m_anims.GetCurrentAnim().GetFrame(), m_player->GetPosition(), b2Vec2(0,0));
	}

	void CPlayerView::Notify(int eventType)
	{
		if (eventType == ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C'))
			ChangeDirection(m_player->GetDirection());
		else if(eventType == ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'))
			OnSpeedChange();
	}

	void CPlayerView::ChangeDirection(DIRECTION dir)
	{
		const bool isIdle = m_player->GetSpeed() == b2Vec2(0,0);
		if (isIdle)
			int f(4);
		if (dir == RIGHT)
		{
			if (!isIdle)
				m_anims.SetCurrentAnim("Walk_Right");
			else 
				m_anims.SetCurrentAnim("Idle_Right");
		}
		else if (dir == LEFT)
		{
			if (!isIdle)
				m_anims.SetCurrentAnim("Walk_Left");
			else
				m_anims.SetCurrentAnim("Idle_Left");
		}
		else if (dir == UP)
		{
			if (!isIdle)
				m_anims.SetCurrentAnim("Walk_Up");
			else
				m_anims.SetCurrentAnim("Idle_Up");
		}
		else if (dir == DOWN)
		{
			if (!isIdle)
				m_anims.SetCurrentAnim("Walk_Down");
			else
				m_anims.SetCurrentAnim("Idle_Down");
		}
	}

	void CPlayerView::OnSpeedChange(void)
	{
		//const bool isIdle = m_player->GetXSpeed() != 0 && m_player->GetYSpeed() != 0;
		//if (isIdle)
		//{
		//	ChangeDirection(m_player->GetDirection());
		//}
		//else
		//{

		//}

		//if (m_player->GetSpeed() == b2Vec2(0,0))
		//{
		//	std::string anim;
		//	const std::string curAnim = m_anims.GetCurrentAnimName();
		//}
		ChangeDirection(m_player->GetDirection());
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