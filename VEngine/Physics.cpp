#include "Physics.h"
#include "ContactListener.h"
#include "DebugDraw.h"

namespace VE
{
	CPhysics::CPhysics(void)
		: m_world(nullptr)
	{
		m_world = new b2World(b2Vec2(0, 10));
		m_debugDrawer = new DebugDraw;
		m_contactListener = new CContactListener(this);

		m_world->SetDebugDraw(m_debugDrawer);
		m_world->SetContactListener(m_contactListener);
	}

	CPhysics::~CPhysics(void)
	{
		delete m_world;
		m_world = nullptr;

		delete m_debugDrawer;
		m_debugDrawer = nullptr;

		delete m_contactListener;
		m_contactListener = nullptr;
	}

	b2Vec2 GameToScreenPosPix(const b2Vec2& posPix)
	{ 
		//return posPix - VE::Renderer()->Cam()->TopLeftPosPix();
		return posPix - b2Vec2(0,0);
	}
}