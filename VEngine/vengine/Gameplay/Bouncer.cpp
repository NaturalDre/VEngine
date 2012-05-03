#include <vengine\Gameplay\Bouncer.h>
#include <vengine\Level\Level.h>
#include <vengine\Application.h>
#include <iostream>
#include <vengine\GameTypes.h>

#define DEFAULTTIMEOUT 1.0f

namespace VE
{
	CBouncer::CBouncer(b2Vec2& pos, float widthMtrs, float heightMtrs)
		:IGameObject("", GOT_BOUNCER)
	{
		{
			b2BodyDef bd;
			bd.type = b2_kinematicBody;
			bd.fixedRotation = true;
			bd.userData = this;
			bd.position = pos;
			bd.allowSleep = false;

			m_body.reset(GetPhysMgr().GetWorld()->CreateBody(&bd));
		}
		{
			b2PolygonShape shape;
			shape.SetAsBox(widthMtrs / 2.0f, widthMtrs / 2.0f);

			b2FixtureDef fd;
			fd.density = DEFAULTDENSITY;
			fd.friction = DEFAULTFRICTION;
			fd.restitution = 0.0f;
			fd.shape = &shape;

			m_body->CreateFixture(&fd);
		}
	}

	CBouncer::CBouncer(Tiled::TiledObject& data)
		: IGameObject("", GOT_BOUNCER)
		, m_timeout(0.0)
	{
		{
			b2BodyDef bd;
			bd.type = b2_kinematicBody;
			bd.fixedRotation = true;
			bd.userData = this;
			bd.position = Utility::GetWorldCenterMtrs(data);

			m_body.reset(GetPhysMgr().GetWorld()->CreateBody(&bd));
		}
		{
			b2PolygonShape shape;
			shape.SetAsBox(Utility::pixToMtr(data.width) / 2.0f, Utility::pixToMtr(data.height) / 2.0f);

			b2FixtureDef fd;
			fd.density = DEFAULTDENSITY;
			fd.friction = DEFAULTFRICTION;
			fd.restitution = 0.0f;
			fd.shape = &shape;

			m_body->CreateFixture(&fd);
		}
	}

	CBouncer::~CBouncer(void)
	{

	}

	void CBouncer::OnBeginContact(b2Contact* contact)
	{
		//if (m_timeout > 0)
		//	return;

		//b2Fixture* fA(contact->GetFixtureA());
		//b2Fixture* fB(contact->GetFixtureB());

		//if (fA->GetBody() == m_body.get())
		//{
		//	fB->GetBody()->SetLinearVelocity(b2Vec2(0,0));
		//	fB->GetBody()->ResetMassData();
		//	fB->GetBody()->ApplyForceToCenter(b2Vec2(0, -553453400));
		//	m_timeout = DEFAULTTIMEOUT;
		//}
		//else if (fB->GetBody() == m_body.get())
		//{
		//	fA->GetBody()->SetLinearVelocity(b2Vec2(0,0));
		//	fB->GetBody()->ResetMassData();
		//	fA->GetBody()->ApplyForceToCenter(b2Vec2(0, -5534534500));
		//	m_timeout = DEFAULTTIMEOUT;
		//}
	}

	void CBouncer::OnEndContact(b2Contact* contact)
	{
		//b2Fixture* fA(contact->GetFixtureA());
		//b2Fixture* fB(contact->GetFixtureB());

		//if (fA->GetBody() == m_body.get())
		//{
		//	fB->GetBody()->ApplyForceToCenter(b2Vec2(0, -553453400));
		//	m_timeout = DEFAULTTIMEOUT;
		//}
		//else if (fB->GetBody() == m_body.get())
		//{
		//	fA->GetBody()->ApplyForceToCenter(b2Vec2(0, -5534534500));
		//	m_timeout = DEFAULTTIMEOUT;
		//}
	}

	void CBouncer::OnPreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		if (m_timeout > 0)
			return;
		b2Fixture* fA(contact->GetFixtureA());
		b2Fixture* fB(contact->GetFixtureB());

		if (fA->GetBody() == m_body.get())
		{
			fB->GetBody()->SetLinearVelocity(b2Vec2(0,0));
			fB->GetBody()->ResetMassData();
			fB->GetBody()->ApplyLinearImpulse(b2Vec2(0, -15), m_body->GetWorldCenter());
			m_timeout = DEFAULTTIMEOUT;
			//contact->SetEnabled(false);
		}
		else if (fB->GetBody() == m_body.get())
		{
			fA->GetBody()->SetLinearVelocity(b2Vec2(0,0));
			fA->GetBody()->ResetMassData();
			fA->GetBody()->ApplyLinearImpulse(b2Vec2(0, -15), m_body->GetWorldCenter());
			m_timeout = DEFAULTTIMEOUT;
			//contact->SetEnabled(false);
		}

	}

	void CBouncer::OnPostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{

	}
	void CBouncer::OnUpdate(void)
	{
		if (m_timeout > 0)
			m_timeout -= GetApp()->DeltaTime();
	}

	int CBouncer::L_Create(lua_State* L)
	{
		Tiled::TiledObject data = Tiled::ToTiledObject(L);
		CBouncer* bouncer = new CBouncer(data);
		GetLvlMgr().AddGameObject(bouncer);
		return 0;
	}

}