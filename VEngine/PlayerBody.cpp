#include "PlayerBody.h"
#include "Player.h"
#include "Physics.h"

namespace VE
{
	CPlayerBody::CPlayerBody(CPlayer* player, b2World* world)
		: m_world(world)
		, m_player(player)
		, m_body(nullptr)
	{
		assert(m_player != nullptr);
		assert(m_world != nullptr);

		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.allowSleep = false;
		bd.bullet = true;
		bd.position.Set(0,0);
		bd.userData = static_cast<void*>(m_player);

		b2FixtureDef fd;
		fd.density = 0.3f;
		fd.friction = 0.3f;
		fd.restitution = 0.0f;
		fd.userData = this;

		b2PolygonShape shape;
		fd.shape = &shape;

		shape.SetAsBox(0.5, 1);

		m_body = m_world->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	CPlayerBody::~CPlayerBody(void)
	{

	}

	b2Vec2 CPlayerBody::Position(void) const
	{
		return m_body->GetPosition();
	}
}