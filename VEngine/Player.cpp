#include "Player.h"
#include "PlayerController.h"
#include <iostream>
#include "PlayerBody.h"
#include "GameLevel.h"
#include "PlayerEvents.h"
#include "Script.h"
#include <luabind\luabind.hpp>
#include "PlayerView.h"
#include <luabind\adopt_policy.hpp>

using namespace VE;

#define EVENT_SPEEDCHANGE ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C')
#define EVENT_DIRCHANGE ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C')

// Calculate impulse needed to simulate moving the desiredVel over one second.
float ImpulseForDistanceX(float desiredVel, b2Body* body)
{
	b2Vec2 vel = body->GetLinearVelocity();
	float velChange = desiredVel - vel.x;
	float impulse = body->GetMass() * velChange;
	return impulse;
}

b2Vec2 ImpulseForDistance(const b2Vec2& desiredVel, b2Body* body)
{
	b2Vec2 vel = body->GetLinearVelocity();
	float xVelChange = desiredVel.x - vel.x;
	float yVelChange = desiredVel.y - vel.y;

	b2Vec2 impulse(0,0);

	impulse.x = body->GetMass() * xVelChange;
	impulse.y = body->GetMass() * yVelChange;

	return impulse;
}

namespace VE
{
	CPlayer::CPlayer(CGameLevel* level, const b2Vec2& spawnPos)
		: IEntity(level)
		, m_body(nullptr)
		, m_speed(0,0)
		, m_vel(5,5)
	{
		m_body = new CPlayerBody(this, spawnPos, GameLevel()->GetPhysics()->World());
		// Set the initial direction of the player.
		SetDirection(RIGHT);
		CPlayerView* view = new CPlayerView(this);
		m_view = view;
		CPlayerController* c = new CPlayerController(this);
		Add(c);
	}

	CPlayer::~CPlayer(void)
	{
		delete m_body;
		m_body = nullptr;

		delete m_view;
		m_view = nullptr;
	}

	/////////////////////////////////////
	////////// CPLAYER //////////////////
	/////////////////////////////////////

	b2Vec2 CPlayer::GetPosition(void) const { return m_body->Position(); }

	void CPlayer::SetXSpeed(float x) 
	{ 
		if (GetXSpeed() != x)
		{
			m_speed.x = x; 
			Notify(EVENT_SPEEDCHANGE);
		}
	}

	void CPlayer::SetYSpeed(float y) 
	{ 
		if (GetYSpeed() != y)
		{
			m_speed.y = y; 
			Notify(EVENT_SPEEDCHANGE);
		}
	}

	void CPlayer::SetSpeed(const b2Vec2& speed) 
	{ 
		if (!(GetSpeed() == speed))
		{
			m_speed = speed; 
			Notify(EVENT_SPEEDCHANGE);
		}
	}

	void CPlayer::Update(double dt)
	{
		IEntity::Update(dt);
		b2Body* body = m_body->Raw();
		body->ApplyLinearImpulse(b2Vec2(ImpulseForDistance(m_speed, body)), body->GetWorldCenter()); 
	}

	void CPlayer::SetDirection(DIRECTION dir)
	{
		// Only update direction if it is a new direction
		if (m_dir != dir)
		{
			m_dir = dir;
			Notify(EVENT_DIRCHANGE);
		}
	}

	void CPlayer::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<CPlayer, bases<IEntity>>("CPlayer")
				.property("speedX", &CPlayer::GetXSpeed, &CPlayer::SetXSpeed)
				.property("speedY", &CPlayer::GetYSpeed, &CPlayer::SetYSpeed)
				.property("speed", &CPlayer::GetSpeed, &CPlayer::SetSpeed)
				.property("position", &CPlayer::GetPosition)
			];

		module(L)
			[
				def("CreatePlayer", &VE::CreatePlayer, adopt(result))
			];
	}

	CPlayer* VE::CreatePlayer(CGameLevel* level, const b2Vec2& spawnPos)
	{
		return new CPlayer(level, spawnPos);
	}
}