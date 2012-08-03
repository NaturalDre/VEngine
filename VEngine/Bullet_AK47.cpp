#include "Bullet_AK47.h"
#include <Box2D\Box2D.h>
#include "GameLevel.h"
#include "Player.h"
#include "Weapon_AK47.h"
#include "Entity.h"
#include <allegro5\altime.h>

namespace VE
{
	Bullet_AK47::Bullet_AK47(b2World* world, Weapon_AK47* weapon, const DIRECTION dir)
		: m_world(world)
		, m_body(nullptr)
		, m_weapon(weapon)
	{
		if (!m_world)
			return;
		m_timeCreated = al_get_time();
		SetDamage(10);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.bullet = true;
		bd.allowSleep = false;
		bd.fixedRotation = true;

		// We don't want all bullets in a straight line
		float r = (-0.5f) + ((rand() % 10) / 10.0f);

		if (dir == RIGHT)
		{
			bd.linearVelocity.Set(10, 0);
			bd.position = GameLevel()->GetPlayer()->Position() + b2Vec2(1, r);
		}
		else if(dir == LEFT)
		{
			bd.linearVelocity.Set(-10, 0);
			bd.position = GameLevel()->GetPlayer()->Position() + b2Vec2(-1, r);
		}
		else if (dir == UP)
		{
			bd.linearVelocity.Set(0, -10);
			bd.position = GameLevel()->GetPlayer()->Position() + b2Vec2(r, -1);
		}
		else if (dir == DOWN)
		{
			bd.linearVelocity.Set(0, 10);
			bd.position = GameLevel()->GetPlayer()->Position() + b2Vec2(r, 1);
		}

		b2FixtureDef fd;
		fd.density = 0.3f;
		fd.friction = 0.0f;
		fd.restitution = 0.0f;
		fd.userData = this;
		fd.isSensor = true;

		b2CircleShape shape;
		shape.m_radius = 0.05f;

		fd.shape = &shape;

		m_body = world->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	Bullet_AK47::Bullet_AK47(b2World* world, Weapon_AK47* weapon, const b2Vec2& pos)
		: m_world(world)
		, m_body(nullptr)
		, m_weapon(weapon)
	{
		if (!m_world)
			return;
		m_timeCreated = al_get_time();
		SetDamage(10);
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.bullet = true;
		bd.allowSleep = false;
		bd.fixedRotation = true;

		// We don't want all bullets in a straight line
		float r = (-0.5f) + ((rand() % 10) / 10.0f);

		auto d = pos - GameLevel()->GetPlayer()->Position();

		bd.linearVelocity = d;
		bd.position = GameLevel()->GetPlayer()->Position(); //+ b2Vec2(r, -1);


		b2FixtureDef fd;
		fd.density = 0.3f;
		fd.friction = 0.0f;
		fd.restitution = 0.0f;
		fd.userData = this;
		fd.isSensor = true;

		b2CircleShape shape;
		shape.m_radius = 0.05f;

		fd.shape = &shape;

		m_body = world->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	void Bullet_AK47::Destroy(void)
	{
		if (m_world && m_body)
			m_world->DestroyBody(m_body);
		m_body = nullptr;
	}

	Bullet_AK47::~Bullet_AK47(void)
	{
		Destroy();
		m_world = nullptr;
		m_weapon = nullptr;
	}

	void Bullet_AK47::BeginContact(b2Contact* contact)
	{
		IEntity* entity = static_cast<IEntity*>(contact->GetFixtureA()->GetBody()->GetUserData());
		if (!entity)
			return;
		if (!entity->OnContact(this))
			return;
		m_weapon->Done(this);
	}
}