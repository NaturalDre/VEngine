#include <vengine\Character\Player.h>
#include <allegro5\allegro5.h>
#include <vengine\Utility.h>
#include <vengine\ObjectManager.h>
#include <vengine\Render\Render.h>

namespace VE
{
	bool MovingLeft(b2Body* body)
	{
		if (!body)
			throw(std::exception("Invalid pointer in MovingLeft"));
		return (body->GetLinearVelocity().x < 0);
	}
	bool MovingRight(b2Body* body)
	{
		if (!body)
			throw(std::exception("Invalid pointer in MovingRight"));
		return (body->GetLinearVelocity().x > 0);
	}

	bool MovingUp(b2Body* body)
	{
		if (!body)
			throw(std::exception("Invalid pointer in MovingUp"));
		return (body->GetLinearVelocity().y < 0);
	}
	bool MovingDown(b2Body* body)
	{
		if (!body)
			throw(std::exception("Invalid pointer in MovingDown"));
		return (body->GetLinearVelocity().y > 0);
	}

	////////////////////////////
	//////// INPUT /////////////
	////////////////////////////
	enum  PLAYERCONTROLS {
		PL_JUMP = ALLEGRO_KEY_W
		, PL_LEFT = ALLEGRO_KEY_A
		, PL_RIGHT = ALLEGRO_KEY_D
	};

	CPlayer::Input::Input(CPlayer* player)
		: m_player(player)
		, m_moveRKeyDown(false)
		, m_moveLKeyDown(false)
		, m_jumpKeyDown(false)
		, m_moveDownKeyDown(false)
		, m_useKeyDown(false)
	{
		assert(m_player != nullptr);
		m_keys.resize(ALLEGRO_KEY_MAX, false);
		m_frameKeyDown.resize(ALLEGRO_KEY_MAX, 0);
	}

	CPlayer::Input::~Input(void)
	{

	}

	void CPlayer::Input::OnUpdate(void)
	{
		/*
		/	Since keyboards don't always auto repeat when a key is held down
		/	the input component needs to check if the relevant keys have not been
		/	released and call the associated functions
		*/
		if (m_jumpKeyDown)
			OnKeyDown(ALLEGRO_KEY_W);
		if (m_moveRKeyDown)
			OnKeyDown(ALLEGRO_KEY_D);
		if (m_moveLKeyDown)
			OnKeyDown(ALLEGRO_KEY_A);
		if (m_moveDownKeyDown)
			OnKeyDown(ALLEGRO_KEY_S);
	}
	void CPlayer::Input::OnKeyDown(int keyCode)
	{
		m_keys[keyCode] = true;
		//Plus one because this function happens outside and before the update function, thus it's 1 frame behind. 
		// (CApplication's update function increments the game tick)
		m_frameKeyDown[keyCode] = GetApp()->GetIngameTicks() + 1;
	}

	void CPlayer::Input::OnKeyUp(int keyCode)
	{
		m_keys[keyCode] = false;
	}

	bool CPlayer::Input::IsKeyDown(int keyCode)
	{
		assert(keyCode < ALLEGRO_KEY_MAX);
		return m_keys[keyCode];
	}

	bool CPlayer::Input::KeyDownThisFrame(int keyCode)
	{
		assert(keyCode < ALLEGRO_KEY_MAX);
		return (m_frameKeyDown[keyCode] == GetApp()->GetIngameTicks());
	}
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
		: m_input(this) // 'this' isn't used in Input's constructor
	{

	}

	CPlayer::~CPlayer(void)
	{

	}

	void CPlayer::Interact(void)
	{

	}

	void CPlayer::OnUpdate(void)
	{
		m_input.OnUpdate();

		{
			float desiredVel = 0.0f;
			if (m_input.IsBothLRKeysDown())
				desiredVel = 0;
			else if(m_input.IsKeyDown(PL_RIGHT) || m_input.RKeyDownThisFrame())
				desiredVel = GetMoveSpeed().x;
			else if(m_input.IsKeyDown(PL_LEFT) || m_input.LKeyDownThisFrame())
				desiredVel = -GetMoveSpeed().x;

			MoveX(desiredVel);
		}
	}

	void CPlayer::CreateBody(b2Vec2& posMtrs, float widthMtrs, float heightMtrs)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.allowSleep = false;
		bd.fixedRotation = true;
		bd.gravityScale = 1.0f;
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

	void CPlayer::CreateBody(const Tiled::TiledObject& data)
	{
		b2Vec2 pos(data.x, data.y);
		CreateBody(Utility::GetWorldCenterMtrs(data), Utility::pixToMtr(data.width), Utility::pixToMtr(data.height));
	}

	CPlayer* CPlayer::Create(void)
	{
		CPlayer* player(new CPlayer);
		return player;
	}

	int CPlayer::L_Create(lua_State* L)
	{
		// STK: table
		Tiled::TiledObject to = Tiled::ToTiledObject(L);
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