#include "Cube.h"
#include "CubeView.h"
#include "Player.h"
#include "GameLevel.h"
#include "Physics.h"
#include "Projectile.h"
#include "Script.h"
#include <luabind\luabind.hpp>
namespace VE
{
	CCube::CCube(CGameLevel* gameLevel, const b2Vec2& spawnPos)
		: IEnemy(gameLevel)
		, m_view(nullptr)
		, m_body(nullptr)
		, m_health(100.0f)
	{
		assert(gameLevel != nullptr);
		m_view = new CCubeView(this, GetGameLevel()->Renderer());

		m_body = CreateBody(*this, spawnPos);
		assert(m_body != nullptr);
	}

	CCube::~CCube(void)
	{
		delete m_view;
		m_view = nullptr;

		GetGameLevel()->Physics()->World()->DestroyBody(m_body);
		m_body = nullptr;
	}

	void CCube::BeginContact(b2Contact* contact)
	{

	}

	void CCube::EndContact(b2Contact* contact) 
	{

	}

	bool CCube::OnContact(IProjectile* projectile)
	{
		if (projectile && m_health > 0)
		{
			m_health -= projectile->GetDamage();
			if(GetScript() && GetScript()->IsValid())
			{
				const luabind::object onDamageTaken = GetScript()->GetSelf()["OnDamageTaken"];
				if (luabind::type(onDamageTaken) == LUA_TFUNCTION)
					luabind::call_function<void>(onDamageTaken);
			}
			if (m_health <= 0)
			{
				m_health = 0;
				if (GetScript() && GetScript()->IsValid())
				{
					const luabind::object onDeath = GetScript()->GetSelf()["OnDeath"];
					if (luabind::type(onDeath) == LUA_TFUNCTION)
						luabind::call_function<void>(onDeath);
				}
			}
		}
		return true;
	}

	b2Body* CCube::CreateBody(CCube& cube, const b2Vec2& spawnPos)
	{
		b2Body* body = nullptr;
		{
			b2BodyDef bd;
			bd.active = true;
			bd.allowSleep = false;
			bd.angle = 0.0f;
			bd.fixedRotation = true;
			bd.bullet = false;
			bd.gravityScale = 0.0f;
			bd.position = spawnPos;
			bd.type = b2_dynamicBody;
			bd.userData = static_cast<IEntity*>(&cube);

			body = cube.GetGameLevel()->Physics()->World()->CreateBody(&bd);
		}
		if (body)
		{
			b2PolygonShape shape;
			shape.SetAsBox(0.5f, 0.5f);
			b2FixtureDef fd;
			fd.shape = &shape;
			fd.userData = static_cast<IContactCallback*>(&cube);
			fd.filter.categoryBits = CATEGORY_ENEMY;
			fd.filter.maskBits = MASK_ENEMY;

			body->CreateFixture(&fd);
		}
		return body;
	}

	void CCube::Update(double dt)
	{
		if (!GetGameLevel() || !m_body)
			return;

		//const b2Vec2 difference = m_body->GetPosition() - GetGameLevel()->GetPlayer()->GetPosition();
		//const float angleOfDifference = GetAngle(m_body->GetPosition(), GetGameLevel()->GetPlayer()->GetPosition());
		//b2Vec2 vel = Rotate(b2Vec2(5, 0), angleOfDifference);
		//m_body->SetLinearVelocity(vel);
		
	}
}