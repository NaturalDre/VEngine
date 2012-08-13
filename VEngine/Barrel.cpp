#include "Barrel.h"
#include <iostream>
#include "Physics.h"
#include "GameLevel.h"

namespace VE
{
	CBarrel::CBarrel(CGameLevel* level)
		:IEntity(level)
		, m_health(100)
	{
		b2BodyDef bd;
		bd.position.Set(10, 10);
		bd.type = b2_staticBody;
		bd.userData = this;

		b2FixtureDef fd;
		fd.density = 0.3f;
		fd.friction = 0.0f;
		fd.restitution = 0.0f;

		b2PolygonShape shape;
		shape.SetAsBox(PixToMtr(300 / 2.0f), PixToMtr(175 / 2.0f));
		fd.shape = &shape;

		m_body = GameLevel()->GetPhysics()->World()->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	CBarrel::~CBarrel(void)
	{
		GameLevel()->GetPhysics()->World()->DestroyBody(m_body);
		m_body = nullptr;
	}

	void CBarrel::Update(double dt)
	{
		IEntity::Update(dt);
	}

	bool CBarrel::OnContact(IProjectile* bullet)
	{
		if (m_health > 0)
		{
			m_health -= 10.0f;
			std::cout << std::endl << "Barrel Health: " << m_health;

			return true;
		}
		return false;
	}
}