#include "Player.h"
#include <iostream>
#include "PlayerBody.h"
#include "GameLevel.h"

namespace VE 
{
	CPlayer::CPlayer(CGameLevel* level)
		: IEntity(level)
		, m_body(nullptr)
	{
		m_body = new CPlayerBody(this, GameLevel()->Physics()->World());
	}

	CPlayer::~CPlayer(void)
	{
		delete m_body;
		m_body = nullptr;
	}

	b2Vec2 CPlayer::Position(void) const
	{
		return m_body->Position();
	}

	void CPlayer::MoveRight(void)
	{
		//++m_pos.x;
	}

	void CPlayer::MoveLeft(void)
	{
		//--m_pos.y;
	}

	void CPlayer::Update(double deltaTime)
	{

	}

	void CPlayer::AdvanceLevel(void)
	{
		//m_publisher.NotifyAll("LevelUp", new LevelUpEvent(this, ++m_level));
	}
}