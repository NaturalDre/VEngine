#include "Player.h"
#include <iostream>
#include "PlayerBody.h"
#include "GameLevel.h"
#include "WeaponAK47.h"
#include "PlayerEvents.h"
#include "Script.h"

using namespace VE;

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
		, m_currentWeapon(nullptr)
	{
		m_body = new CPlayerBody(this, spawnPos, GameLevel()->Physics()->World());

		m_weapons.push_back(new CWeaponAK47(GameLevel(), this));

		m_currentWeapon = m_weapons.front();
		// Set the initial direction of the player.
		SetDirection(RIGHT);
		// The script that will set the player's actions.
		// TO DO: Add the ability to change what script is used.
		SetScript(new CScript(GetGameLevel()->GetScriptEnv(), "PlayerScript"));
	}

	CPlayer::~CPlayer(void)
	{
		delete m_body;
		m_body = nullptr;

		SetScript(nullptr);
		m_currentWeapon = nullptr;
	}

	/////////////////////////////////////
	////////// CPLAYER //////////////////
	/////////////////////////////////////

	void CPlayer::SubscribeTo(const std::string& topic, IObserver* observer)
	{
		m_publisher.Register(topic, observer);
	}

	void CPlayer::SubscribeFrom(const std::string& topic, IObserver* observer)
	{
		m_publisher.Deregister(topic, observer); 
	}

	void CPlayer::SubscribeFromAll(IObserver* observer)
	{
		m_publisher.Deregister(observer);
	}

	b2Vec2 CPlayer::GetPosition(void) const { return m_body->Position(); }

	void CPlayer::SetXSpeed(float x) 
	{ 
		if (GetXSpeed() != x)
		{
			m_speed.x = x; 
			m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'));
		}
	}

	void CPlayer::SetYSpeed(float y) 
	{ 
		if (GetYSpeed() != y)
		{
			m_speed.y = y; 
			m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'));
		}
	}

	void CPlayer::SetSpeed(const b2Vec2& speed) 
	{ 
		if (!(GetSpeed() == speed))
		{
			m_speed = speed; 
			m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'));
		}
	}

	void CPlayer::Update(double deltaTime)
	{
		if (GetCurrentWeapon())
			GetCurrentWeapon()->Update(deltaTime);
		b2Body* body = m_body->Raw();

		body->ApplyLinearImpulse(b2Vec2(ImpulseForDistance(m_speed, body)), body->GetWorldCenter()); 
	}

	void CPlayer::SetDirection(DIRECTION dir)
	{
		// Only update direction if it is a new direction
		if (m_dir != dir)
		{
			m_dir = dir;
			m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C'));
		}
	}

	CPlayer* VE::CreatePlayer(CGameLevel* level, const b2Vec2& spawnPos)
	{
		return new CPlayer(level, spawnPos);
	}
}