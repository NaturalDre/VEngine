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
		m_bitmap = CBitmap("box.png");
		m_anims.SetSpriteSheet("player.png", 4, 3, 5); 
		m_anims.AddFrameSequence(FrameSequence(1, 3), "WalkDown");
		m_anims.AddFrameSequence(FrameSequence(4, 6), "WalkLeft");
		m_anims.AddFrameSequence(FrameSequence(10, 12), "WalkUp");
		m_anims.AddFrameSequence(FrameSequence(7, 9), "WalkRight");
		//CBitmap t = m_bitmap;
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

		//VE::DrawBitmap(m_bitmap, m_player->Position(), b2Vec2(0,0));
		VE::DrawBitmap(m_anims.GetCurrentAnim().GetFrame(), m_player->Position(), b2Vec2(0,0));
	}

	void CPlayerView::Notify(IEvent* ev)
	{
		if (ev->Type() == ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C'))
		{
			Direction dir = static_cast<DirectionChanged*>(ev)->GetDir();

			if (dir == e_Right)
				m_anims.SetCurrentAnim("WalkRight");
			else if (dir == e_Left)
				m_anims.SetCurrentAnim("WalkLeft");
			else if (dir == e_Up)
				m_anims.SetCurrentAnim("WalkUp");
			else if (dir == e_Down)
				m_anims.SetCurrentAnim("WalkDown");
			//if (dir == e_Right)
				//m_anims.cu
		}
	}

	void CPlayerView::SetPlayer(CPlayer* player)
	{
		if (m_player)
			m_player->SubscribeFromAll(this);

		m_player = player;

		if (m_player)
		{
			m_player->SubscribeTo("LevelUp", this);
			m_player->SubscribeTo("DirectionChanged", this);
		}
	}
}