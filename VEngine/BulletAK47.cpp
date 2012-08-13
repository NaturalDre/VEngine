#include "BulletAK47.h"
#include <Box2D\Box2D.h>
#include "GameLevel.h"
#include "Player.h"
#include "WeaponAK47.h"
#include "Entity.h"
#include <allegro5\altime.h>

namespace VE
{
	CBulletAK47::CBulletAK47(b2World* world, CWeaponAK47* weapon, const b2Vec2& pos)
		: m_world(world)
		, m_body(nullptr)
		, m_weapon(weapon)
		, m_done(false)
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

		{
			// We don't want all bullets in a straight line
			float random = (-0.5f) + ((rand() % 100) / 100.0f);

			const b2Vec2 angleVec = pos - GameLevel()->GetPlayer()->GetPosition();
			const float angleDegrees = GetAngle(GameLevel()->GetPlayer()->GetPosition(), pos);

			b2Vec2 vel = Rotate(b2Vec2(10, random), angleDegrees);

			bd.linearVelocity = vel;
			bd.position = GameLevel()->GetPlayer()->GetPosition(); //+ b2Vec2(r, -1);
		}

		b2FixtureDef fd;
		fd.density = 0.3f;
		fd.friction = 0.0f;
		fd.restitution = 0.0f;
		fd.userData = this;
		//fd.isSensor = true;

		b2CircleShape shape;
		shape.m_radius = 0.05f;

		fd.shape = &shape;

		m_body = world->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	void CBulletAK47::Destroy(void)
	{
		if (m_world && m_body)
			m_world->DestroyBody(m_body);
		m_body = nullptr;
	}

	CBulletAK47::~CBulletAK47(void)
	{
		Destroy();
		m_world = nullptr;
		m_weapon = nullptr;
	}

	void CBulletAK47::BeginContact(b2Contact* contact)
	{
		m_done = true;
	}
}