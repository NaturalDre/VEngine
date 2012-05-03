#include <vengine\Character\Player.h>
#include <allegro5\allegro5.h>
#include <vengine\Utility.h>
#include <vengine\ObjectManager.h>
#include <vengine\Render\Render.h>
#include <vengine\Script\Script.h>
#include <vengine\GameTypes.h>

#include <iostream>
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

	// CPlayer Definitions
	CPlayer::CPlayer(void)
		: m_input(nullptr) // 'this' isn't used in Input's constructor so the warning by the compiler may be ignored.
		, m_feetFixture(nullptr)
	{
		m_render.reset(new CPlayerRender(this));
		m_input = new CPlayerInput(this);
	}

	CPlayer::~CPlayer(void)
	{

	}

	void CPlayer::Interact(void)
	{

	}

	bool CPlayer::IsGrounded(void) const
	{
		if (!m_feetTouching.empty())
			return true;
		return false;
	}

	void CPlayer::OnUpdate(void)
	{
		m_input->OnUpdate();

		if (m_input->IsJumpKeyDown() && IsGrounded())
			GetBody()->ApplyForceToCenter(b2Vec2(0, -300 * GetBody()->GetMass()));

		{
			float desiredVel = 0.0f;
			if (m_input->IsBothLRKeysDown())
				desiredVel = 0;
			else if(m_input->IsKeyDown(PL_RIGHT) || m_input->RKeyDownThisFrame())
				desiredVel = GetMoveSpeed().x;
			else if(m_input->IsKeyDown(PL_LEFT) || m_input->LKeyDownThisFrame())
				desiredVel = -GetMoveSpeed().x;

			if (desiredVel - GetBody()->GetLinearVelocity().x != 0)
				MoveX(desiredVel);
		}
	}

	void CPlayer::OnBeginContact(b2Contact* contact)
	{

		b2Fixture* us(nullptr);
		b2Fixture* them(nullptr);

		if (contact->GetFixtureA()->GetBody() == GetBody())
		{
			us = contact->GetFixtureA();
			them = contact->GetFixtureB();
		}
		else
		{
			us = contact->GetFixtureB();
			them = contact->GetFixtureA();
		}

		// Handle begin feet collision
		{
			if (us == m_feetFixture)
			{
				m_feetTouching.insert(them);
				return;
			}
			else if (us == m_feetFixture)
			{
				m_feetTouching.insert(them);
				return;
			}
		}

		// Handle begin body collision
		if (them->GetBody()->GetUserData() && them->GetBody()->GetUserData()->GetTypeID() == GOT_BOUNCER)
			std::cout << std::endl << "Began touch of bouncer.";
	}

	void CPlayer::OnEndContact(b2Contact* contact)
	{

		// Handle end feet collision 
		{
			if (contact->GetFixtureA() == m_feetFixture)
			{
				m_feetTouching.erase(contact->GetFixtureB());
			}
			else if (contact->GetFixtureB() == m_feetFixture)
			{
				m_feetTouching.erase(contact->GetFixtureA());
			}
		}
	}

	void CPlayer::HandleBeginContact(b2Fixture* us, b2Fixture* them)
	{

	}

	void CPlayer::HandleEndContact(b2Fixture* us, b2Fixture* them)
	{

	}

	void CPlayer::CreateBody(b2Vec2& posMtrs, float widthMtrs, float heightMtrs)
	{
		m_characterWidth = widthMtrs;
		m_characterHeight = heightMtrs;
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
			fd.friction = 0.0f;

			m_body.reset(GetPhysMgr().GetWorld()->CreateBody(&bd));
			m_body->CreateFixture(&fd);
		}
		{
			b2PolygonShape shape;
			shape.SetAsBox(GetCharacterWidth() / 2.5f, 0.001, b2Vec2(0, GetCharacterHeight() / 2.0f), 0.0f);

			b2FixtureDef fd;
			fd.density = DEFAULTDENSITY;
			fd.shape = &shape;
			fd.isSensor = true;

			m_feetFixture = m_body->CreateFixture(&fd);
		}

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

		for (auto iter = to.properties.begin(); iter != to.properties.end(); ++iter)
		{
			if (Tiled::IsScriptName((*iter).first))
			{
				CLuaScript* script = GetScriptMgr().LoadScript((*iter).second);
				if (script)
					player->AttachScript(script);
			}
		}

		// Remove the passed TileObject table from Lua's stack.
		lua_pop(L, 1);
		// STK:
		return 0;
	}


	////////////////////////////
	//////// INPUT /////////////
	////////////////////////////

	CPlayerInput::CPlayerInput(CPlayer* player)
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

	CPlayerInput::~CPlayerInput(void)
	{

	}

	void CPlayerInput::OnUpdate(void)
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
	void CPlayerInput::OnKeyDown(int keyCode)
	{
		m_keys[keyCode] = true;
		//Plus one because this function happens outside and before the update function, thus it's 1 frame behind. 
		// (CApplication's update function increments the game tick)
		m_frameKeyDown[keyCode] = GetApp()->GetIngameTicks() + 1;
	}

	void CPlayerInput::OnKeyUp(int keyCode)
	{
		m_keys[keyCode] = false;
	}

	bool CPlayerInput::IsKeyDown(int keyCode)
	{
		assert(keyCode < ALLEGRO_KEY_MAX);
		return m_keys[keyCode];
	}

	bool CPlayerInput::KeyDownThisFrame(int keyCode)
	{
		assert(keyCode < ALLEGRO_KEY_MAX);
		return (m_frameKeyDown[keyCode] == GetApp()->GetIngameTicks());
	}


	// CPlayerRender Definitions
	CPlayerRender::CPlayerRender(CPlayer* player)
		: m_player(player)
		, m_animation("Images/test.png", 1, 6, 10)
	{
		m_animation.SetAlpha(16,32,48);
	}

	CPlayerRender::~CPlayerRender(void)
	{

	}

	void CPlayerRender::Draw(void)
	{
		// Test code below
		VE::Draw(m_animation.GetFrame(), b2Vec2(1, 38), 0);
	}
}
