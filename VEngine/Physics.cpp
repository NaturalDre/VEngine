#include "Physics.h"
#include "Application.h"
#include "Render.h"
#include "DebugDraw.h"
#include "TMR\TiledObject.h"

namespace VE 
{
	const size_t VELOCITYITERS(6);
	const size_t POSITIONITERS(6);
	const float TIMESTEP(1.0f / 60.0f);

	CPhysics* PHYSICS = nullptr;

	CPhysics::CPhysics(void)
	{
		m_world = new b2World(b2Vec2(0, 10));

		m_contactListener = new CContactListener(this);
		m_world->SetContactListener(m_contactListener);

		m_debugDraw = new DebugDraw;
		m_world->SetDebugDraw(m_debugDraw);

		PHYSICS = this;
	}

	CPhysics::~CPhysics(void)
	{
		delete m_world;
		m_world = nullptr;

		delete m_contactListener;
		m_contactListener = nullptr;

		delete m_debugDraw;
		m_debugDraw = nullptr;
		PHYSICS = nullptr;
	}

	void CPhysics::ProcessPhysicsLayer(void)
	{
		Tiled::CObjectLayer* physlayer = App()->GetMap().PhysicsLayer();

		if (!physlayer)
			return;

		for (auto iter = physlayer->Objects().begin(); iter != physlayer->Objects().end(); ++iter)
		{


			b2BodyDef bd;
			bd.type = b2_staticBody;
			bd.position = GetWorldCenterMtrs(*iter);

			b2PolygonShape shape;
			shape.SetAsBox(PixToMtr(iter->Width() / 2.0f), PixToMtr(iter->Height() / 2.0f), b2Vec2(0,0), 0.0f);

			b2Body* body = m_world->CreateBody(&bd);

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.3f;

			body->CreateFixture(&fd);
			m_mapBodies.push_back(body);
		}

	}
	void CPhysics::Step(void)
	{
		m_world->Step(TIMESTEP, VELOCITYITERS, POSITIONITERS);
	}

	void CPhysics::Free(void)
	{
		delete PHYSICS;
		PHYSICS = nullptr;
	}

	CPhysics* Physics(void)
	{
		return PHYSICS;
	}

	b2World* World(void)
	{
		return Physics()->World();
	}

	b2Vec2 GameToScreenPosPix(const b2Vec2& posPix)
	{ 
		return posPix - VE::Renderer()->Cam()->TopLeftPosPix();
	}

	b2Vec2 GetWorldCenterMtrs(const Tiled::TiledObject& obj) 
	{ 
		b2Vec2 pos(obj.X(), obj.Y());
		return TiledToBoxCoords(pos, obj.Width(), obj.Height());
	}
}	

