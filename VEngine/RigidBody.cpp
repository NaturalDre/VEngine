#include "RigidBody.h"
#include <luabind\object.hpp>
#include "TMR\Object.h"
#include "GameLevel.h"

namespace VE
{
	CRigidBody::CRigidBody(const luabind::adl::object& obj)
		: m_body(nullptr)
	{
		if (luabind::type(obj) != LUA_TTABLE)
			return;

		Tiled::Object to(obj);

		b2BodyDef bd;
		bd.type = b2_staticBody;
		bd.position = TiledToBoxCoords(to);
		b2FixtureDef fd;

		b2PolygonShape shape;
		fd.shape = &shape;

		shape.SetAsBox(PixToMtr(to.Width()) / 2.0f, PixToMtr(to.Height()) / 2.0f);
		
		m_body = GameLevel()->Physics()->World()->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	void CRigidBody::Free(void)
	{
		GameLevel()->Physics()->World()->DestroyBody(m_body);
		m_body = nullptr;
	}

	CRigidBody::~CRigidBody(void)
	{
		Free();
	}
}