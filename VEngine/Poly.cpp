#include "Poly.h"
#include "Physics.h"
#include <Box2D\Box2DUtil.h>
CPoly::CPoly(void)
	: m_body(nullptr)
{	b2Vec2 verts[7];
	verts[0] = b2Vec2(-1,-2);
	verts[1] = b2Vec2(1,-1);
	verts[2] = b2Vec2(0,-1);
	verts[3] = b2Vec2(0,0);
	verts[4] = b2Vec2(1,0);
	verts[5] = b2Vec2(1,1);
	verts[6] = b2Vec2(-1, 1);

	b2Polygon poly(verts, 7);
	b2FixtureDef fd;
	b2PolygonShape shape;
	b2BodyDef bd;
	b2Body* body = VE::World()->CreateBody(&bd);

	DecomposeConvexAndAddTo(&poly, body, &fd);

	//fd.shape = &shape;

	//b2Vec2 verts[7];
	//verts[0] = b2Vec2(-1,-2);
	//verts[1] = b2Vec2(1,-1);
	//verts[2] = b2Vec2(0,-1);
	//verts[3] = b2Vec2(0,0);
	//verts[4] = b2Vec2(1,0);
	//verts[5] = b2Vec2(1,1);
	//verts[6] = b2Vec2(-1, 1);

	//shape.Set(verts, 7);

	//b2Vec2 verts[4];
	//verts[0] = b2Vec2(-1, -1);
	//verts[1] = b2Vec2(1,-1);
	//verts[2] = b2Vec2(1,1);
	//verts[3] = b2Vec2(-1,1);

	//shape.Set(verts, 4);

	//b2BodyDef bd;
	//bd.position = b2Vec2(5,5);
	//m_body = VE::World()->CreateBody(&bd);

	//m_body->CreateFixture(&fd);

	//VE::CPolygonSeperator sp(verts, 4);
}

CPoly::~CPoly(void)
{
	VE::World()->DestroyBody(m_body);
	m_body = nullptr;
}