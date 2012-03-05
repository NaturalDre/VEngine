#include "vengine\Physics.h"
#include "vengine\Level\Level.h"
#include "vengine\Render\Render.h"
#include <vengine\ContactListener.h>
#include <vengine\DebugDraw.h>
#include <vengine\Utility.h>

namespace VE
{
	const float SCALE(32.0f);
	const size_t VELOCITYITERS(6);
	const size_t POSITIONITERS(6);
	const float TIMESTEP(1.0f / Global::FPS);
	const b2Vec2 GRAVITY(0, 30);

	////////////////////////////////
	////////// TILED OBJECT ////////
	////////////////////////////////

	Utility::TiledObject::TiledObject(Utility::TiledObject&& rhs)
				: name(rhs.name)
				, type(rhs.type)
				, x(rhs.x)
				, y(rhs.y)
				, width(rhs.width)
				, height(rhs.height)
				, properties(std::move(rhs.properties)) { }

	CPhysicsManager::CPhysicsManager(void)
	{
		m_world.reset(new b2World(b2Vec2(0, 10)));
		if (!m_world)
			throw("Unable to allocate memory for b2World");
		m_contactListener.reset(new CContactListener);
		m_world->SetContactListener(m_contactListener.get());
		m_debugDraw.reset(new DebugDraw);
		m_world->SetDebugDraw(m_debugDraw.get());
	}

	bool CPhysicsManager::BodyExists(b2Body* body)
	{
		for (b2Body* p = m_world->GetBodyList(); p; p = p->GetNext())
		{
			if (p == body)
				return true;
		}

		return false;
	}

	bool CPhysicsManager::BodyExists(void* body)
	{
		return BodyExists(static_cast<b2Body*>(body));
	}

	void CPhysicsManager::UpdateWorld(void)
	{
		m_world->Step(TIMESTEP, VELOCITYITERS, POSITIONITERS);
		m_world->ClearForces();
	}

	void CPhysicsManager::DrawDebugData(void)
	{
		m_world->DrawDebugData();
	}

	CPhysicsManager& GetPhysMgr(void)
	{
		static CPhysicsManager instance;
		return instance;
	}

	b2Vec2 Utility::GameToScreenPosPix(const b2Vec2& posPix) 
	{ 
		return posPix - GetRenderMgr().GetCam()->GetTopLeftPix();
	}

	//// How many vertices does this polygon contain?
	//size_t GetVertCount(const LuaPlus::LuaObject obj)
	//{
	//	LuaPlus::LuaObject polygon = obj.GetByName("polygon");
	//	return polygon.GetTableCount();
	//}

	//// Get all the vertices of the polygon object. (Only use on LuaObjects you know are polygons)
	//b2Vec2* GetVerts(const LuaPlus::LuaObject obj)
	//{
	//	const size_t count = GetVertCount(obj);

	//	LuaPlus::LuaObject polygon = obj.GetByName("polygon");
	//	b2Vec2* verts = new b2Vec2[count];

	//	for (size_t i(0); i < count; ++i)
	//	{
	//		verts[i].Set(
	//			Utility::pixToMtr(polygon.GetByIndex(i + 1).GetByName("x").GetFloat()),
	//			Utility::pixToMtr(polygon.GetByIndex(i + 1).GetByName("y").GetFloat()));
	//	}
	//	return verts;
	//}

	int Utility::CreateSolidGround(lua_State* L)
	{
		Utility::TiledObject data = Utility::ToTiledObject(L);

		b2Vec2 pos = Utility::GetWorldCenterMtrs(data);
		//b2Vec2 pos(data.x, data.y);
		//pos = Utility::pixToMtr(pos);
		
		b2BodyDef bd;
		bd.type = b2_staticBody;
		bd.position = pos;

		b2PolygonShape shape;
		shape.SetAsBox(Utility::pixToMtr(data.width / 2.0f), Utility::pixToMtr(data.height / 2.0f));

		b2Body* body = GetPhysMgr().GetWorld()->CreateBody(&bd);

		b2FixtureDef fd;
		fd.density = DEFAULTDENSITY;
		fd.shape = &shape;
		fd.friction = DEFAULTFRICTION;
		body->CreateFixture(&fd);

		GetLvlMgr().GetLevelLoader()->AddBody(body);

		return 0;
		//b2Vec2 pos(0,0);
		//b2Body* body(nullptr);
		//b2BodyDef bd;
		//b2PolygonShape shape;

		////if (data.GetByName("polygon").IsNil())
		////{
		////	pos = Reader::GetWorldCenterMtrs(data);
		////	bd.position = pos;
		////	bd.type = b2_staticBody;

		////	body = GetPhysMgr().GetWorld()->CreateBody(&bd);
		////	if (!body)
		////		throw("Unable to allocate memory for poly body in CreateSolidGround");

		////	shape.SetAsBox(Reader::GetWidthMtrs(data) / 2.0f, Reader::GetHeightMtrs(data) / 2.0f);
		////}
		////else
		////{
			//pos.Set(Reader::GetXMtrs(data), Reader::GetYMtrs(data));

			//bd.position = pos;
			//bd.type = b2_staticBody;

			//body = GetPhysMgr().GetWorld()->CreateBody(&bd);
			//if (!body)
			//	throw("Unable to allocate memory for reg body in CreateSolidGround");
			//shape.Set(GetVerts(data), GetVertCount(data));
		////}

		//body->CreateFixture(&shape, 0);
		//GetLvlMgr().GetLevelLoader()->AddBody(body);
	}
}