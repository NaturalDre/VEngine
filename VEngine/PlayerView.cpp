#include "PlayerView.h"
#include "Player.h"
#include <iostream>
#include <allegro5\allegro5.h>

namespace VE
{
	CPlayerView::CPlayerView(CRender* render)
		: IView(render)
		, m_player(nullptr)
	{
		m_bitmap = CBitmap("box.png");
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
		VE::DrawBitmap(m_bitmap, m_player->Position(), b2Vec2(0,0));
		
	}

	void CPlayerView::Notify(IEvent* ev)
	{
		
	}

	void CPlayerView::SetPlayer(CPlayer* player)
	{
		if (m_player)
			m_player->SubscribeFromAll(this);

		m_player = player;

		if (m_player)
			m_player->SubscribeTo("LevelUp", this);
	}
}