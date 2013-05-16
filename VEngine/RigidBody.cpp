#include "RigidBody.h"
#include <luabind\luabind.hpp>
#include "TMR\TiledObject.h"
#include "GameLevel.h"

namespace VE
{
	CRigidBody::CRigidBody(lua_State* L)
		: m_body(nullptr)
	{
		if (lua_istable(L, -1))
			return;
		Tiled::Object to(L);
		b2BodyDef bd;
		bd.type = b2_staticBody;
		bd.position = TiledToBoxCoords(to);
		b2FixtureDef fd;

		b2PolygonShape shape;
		fd.shape = &shape;

		shape.SetAsBox(PixToMtr(to.Width()) / 2.0f, PixToMtr(to.Height()) / 2.0f);
		
		m_body = GameLevel()->GetPhysics()->World()->CreateBody(&bd);
		m_body->CreateFixture(&fd);
	}

	CRigidBody::~CRigidBody(void)
	{
		Free();
	}

	void CRigidBody::Free(void)
	{
		GameLevel()->GetPhysics()->World()->DestroyBody(m_body);
		m_body = nullptr;
	}



	void CRigidBody::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<CRigidBody>("CRigidBody")
				.def("Free", &CRigidBody::Free)
			];
	}
}