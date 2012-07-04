#include "Bullet_AK47.h"
#include <Box2D\Box2D.h>
#include "GameLevel.h"
#include "Player.h"
#include "Weapon_AK47.h"

namespace VE
{
	Bullet_AK47::Bullet_AK47(b2World* world, Weapon_AK47* weapon, const Direction dir)
		: m_body(nullptr)
		, m_weapon(weapon)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.bullet = true;
		bd.allowSleep = false;
		bd.fixedRotation = true;


		//const Direction dir = dir;
		if (dir == e_Right)
		{
			bd.linearVelocity.Set(10, 0);
			bd.position = GameLevel()->Player()->Position() + b2Vec2(2, 0);
		}
		else if(dir == e_Left)
		{
			bd.linearVelocity.Set(-10, 0);
			bd.position = GameLevel()->Player()->Position() + b2Vec2(-2, 0);
		}
		else if (dir == e_Up)
		{
			bd.linearVelocity.Set(0, -10);
			bd.position = GameLevel()->Player()->Position() + b2Vec2(0, -2);
		}
		else if (dir == e_Down)
		{
			bd.linearVelocity.Set(0, 10);
			bd.position = GameLevel()->Player()->Position() + b2Vec2(0, 2);
		}

		b2FixtureDef fd;
		fd.density = 0.3f;
		fd.friction = 0.0f;
		fd.restitution = 0.0f;
		fd.userData = this;
		fd.isSensor = true;

		//fd.filter.categoryBits = e_FriendlyBullet;
		//fd.filter.maskBits = e_Enemy | e_Static;

		b2CircleShape shape;
		shape.m_radius = 0.05f;

		fd.shape = &shape;

		m_body = world->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	Bullet_AK47::~Bullet_AK47(void)
	{
		GameLevel()->Physics()->World()->DestroyBody(m_body);
		m_body = nullptr;
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

		//GameLevel()->Physics()->World()->DestroyBody(m_body);
		//m_body = nullptr;
	}
}