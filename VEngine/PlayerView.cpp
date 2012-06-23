#include "PlayerView.h"
#include "Player.h"
#include <iostream>
#include "LevelUpEvent.h"

namespace VE
{
	CPlayerView::CPlayerView(CRender* render)
		: IView(render)
		, m_player(nullptr)
		, m_leveled(false)
	{

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

		std::cout << std::endl << "Drawing player at position (" << m_player->Position().x << ',' << m_player->Position().y << ')';
		if (m_leveled)
			std::cout << " with the level[" << m_level << " up animation.";
		m_leveled = false;
	}

	void CPlayerView::Notify(IEvent* ev)
	{
		if (ev->Type() == ALLEGRO_GET_EVENT_TYPE('L', 'V', 'L', 'U'))
		{
			m_leveled = true;
			LevelUpEvent* lvlEv = static_cast<LevelUpEvent*>(ev);
			m_level = lvlEv->Level();
		}
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