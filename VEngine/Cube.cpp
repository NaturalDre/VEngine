#include "Cube.h"
#include "CubeView.h"
#include "Player.h"
#include "GameLevel.h"
#include "Physics.h"
#include "Projectile.h"
#include "Script.h"
#include <luabind\luabind.hpp>

const char* OnDamageTaken = "OnDamageTaken";

namespace VE
{
	CCube::CCube(CGameLevel* gameLevel, const b2Vec2& spawnPos)
		: IEnemy(gameLevel)
		, m_view(nullptr)
		, m_body(nullptr)
		, m_health(100.0f)
		, m_deleteOnDeath(true)
	{
		assert(gameLevel != nullptr);
		m_view = new CCubeView(this, GetGameLevel()->GetRenderer());

		m_body = CreateBody(*this, spawnPos);
		assert(m_body != nullptr);

		SetScript(new CScript(GetGameLevel()->GetScriptEnv(), "CubeScript"));
		GetScript()->GetSelf()["cube"] = this;
	}

	CCube::~CCube(void)
	{
		delete m_view;
		m_view = nullptr;

		GetGameLevel()->GetPhysics()->World()->DestroyBody(m_body);
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
				try
				{
					if (luabind::gettable(GetScript()->GetSelf(), OnDamageTaken))
						luabind::call_member<void>(GetScript()->GetSelf(), OnDamageTaken);
				}
				catch(const luabind::error& e)
				{
					const std::string str = lua_tostring(e.state(), -1);
					lua_pop(e.state(), 1);
				}
			}
			if (m_health <= 0)
			{
				m_health = 0;
				GetGameLevel()->MarkForDeletion(this);
			}
			return true;
		}
	}

	void CCube::OnDeath(void)
	{
		m_health = 0;
		if (GetDeleteOnDeath())
			GetGameLevel()->MarkForDeletion(this);
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

			body = cube.GetGameLevel()->GetPhysics()->World()->CreateBody(&bd);
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
	}

	void CCube::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<CCube, IEnemy>("CCube")
				.property("body", &CCube::GetBody)
				.property("health", &CCube::GetHealth)
			];
	}
}