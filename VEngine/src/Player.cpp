#include <vengine\Character\Player.h>
#include <allegro5\allegro5.h>
#include <vengine\Utility.h>
#include <vengine\ObjectManager.h>
#include <vengine\Render\Render.h>

namespace VE
{
	////////////////////////////
	///////// RENDER ///////////
	////////////////////////////

	CPlayer::Render::Render(CPlayer* player)
		: m_player(player)
		, m_animation(4, 4, 5)
	{
		
	}

	/////////////////////////////
	/////// CPlayer /////////////
	/////////////////////////////

	CPlayer::CPlayer(void)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.allowSleep = false;
		bd.fixedRotation = true;
		bd.gravityScale = 0.0f;
		bd.userData = this;

		b2PolygonShape shape;
		shape.SetAsBox(2,4);

		b2FixtureDef fd;
		fd.density = DEFAULTDENSITY;
		fd.shape = &shape;


		m_body.reset(GetPhysMgr().GetWorld()->CreateBody(&bd));
		m_body->CreateFixture(&fd);
		//m_body.reset(GetPhysMgr().GetWorld
	}

	CPlayer::~CPlayer(void)
	{

	}

	void CPlayer::Interact(void)
	{

	}

	void CPlayer::OnUpdate(void)
	{

	}

	void CPlayer::CreateBody(b2Vec2& posMtrs, float widthMtrs, float heightMtrs)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.allowSleep = false;
		bd.fixedRotation = true;
		bd.gravityScale = 0.0f;
		bd.position = posMtrs;
		bd.userData = this;

		b2PolygonShape shape;
		shape.SetAsBox(widthMtrs / 2.0f, heightMtrs / 2.0f);

		b2FixtureDef fd;
		fd.density = DEFAULTDENSITY;
		fd.shape = &shape;


		m_body.reset(GetPhysMgr().GetWorld()->CreateBody(&bd));
		m_body->CreateFixture(&fd);
	}

	void CPlayer::CreateBody(const Utility::TiledObject& data)
	{
		b2Vec2 pos(data.x, data.y);
		CreateBody(Utility::pixToMtr(pos), Utility::pixToMtr(data.width), Utility::pixToMtr(data.height));
	}

	CPlayer* CPlayer::Create(void)
	{
		CPlayer* player(new CPlayer);
		return player;
	}

	int CPlayer::L_Create(lua_State* L)
	{
		// STK: table
		Utility::TiledObject to = Utility::ToTiledObject(L);
		// Create the player instance
		CPlayer* player = Create();
		// Create the body for the player based on information from
		// the TiledObject passed to use from Lua.
		player->CreateBody(to);
		// Let the object manager know who the player is.
		GetObjMgr().SetPlayer(player);
		// Set the player as the target to follow for the camera
		GetRenderMgr().GetCam()->SetTarget(player);
		// Remove the passed TileObject table from Lua's stack.
		lua_pop(L, 1);
		// STK:
		return 0;
	}
}