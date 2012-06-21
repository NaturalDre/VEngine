#include "Player.h"
#include <iostream>
#include "LevelUpEvent.h"

namespace VE 
{
	CPlayer::CPlayer(void)
		: m_pos(0,0)
		, m_level(1)
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

	void CPlayer::Update(double deltaTime)
	{

	}

	void CPlayer::AdvanceLevel(void)
	{
		m_publisher.NotifyAll("LevelUp", new LevelUpEvent(this, ++m_level));
	}
}