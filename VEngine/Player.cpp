#include "Player.h"
#include <iostream>

namespace VE 
{
	CPlayer::CPlayer(void)
		: m_pos(0,0)
	{

	}

	void CPlayer::MoveRight(void)
	{
		++m_pos.x;
	}

	void CPlayer::MoveLeft(void)
	{
		--m_pos.y;
	}
}