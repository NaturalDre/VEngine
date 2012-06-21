#include "PlayerView.h"
#include "Player.h"
#include <iostream>

namespace VE
{
	CPlayerView::CPlayerView(CRender* render)
		: IView(render)
		, m_player(nullptr)
	{

	}

	CPlayerView::~CPlayerView(void)
	{

	}

	void CPlayerView::Draw(void)
	{
		if (!m_player)
			return;

		std::cout << std::endl << "Player is at position (" << m_player->Position().x << ',' << m_player->Position().y << ')';
	}

	void CPlayerView::SetPlayer(CPlayer* player)
	{
		m_player = player;
	}
}