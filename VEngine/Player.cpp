#include "Player.h"
#include <iostream>
#include "PlayerBody.h"
#include "GameLevel.h"
#include "Weapon_AK47.h"
#include "PlayerEvents.h"

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
	class CPlayerImpl: public CPlayer
	{
		friend CPlayer;
	public:
		CPlayerImpl(CGameLevel* level, const b2Vec2& spawnPos);
		~CPlayerImpl(void);

	private:
		CObservable m_publisher;
		CPlayerBody* m_body;
		b2Vec2 m_speed;
		b2Vec2 m_vel;
		DIRECTION m_dir;
		IWeapon* m_currentWeapon;
		std::list<IWeapon*> m_weapons;
	};
}

inline CPlayerImpl* Impl(CPlayer* player) { return static_cast<CPlayerImpl*>(player); }
inline const CPlayerImpl* Impl(const CPlayer* player) { return static_cast<const CPlayerImpl*>(player); }

CPlayerImpl::CPlayerImpl(CGameLevel* level, const b2Vec2& spawnPos)
	: CPlayer(level)
	, m_body(nullptr)
	, m_speed(0,0)
	, m_vel(5,5)
	, m_currentWeapon(nullptr)
{
	m_body = new CPlayerBody(this, spawnPos, GameLevel()->Physics()->World());
	
	m_weapons.push_back(new Weapon_AK47(GameLevel(), this));

	m_currentWeapon = m_weapons.front();

	SetDirection(RIGHT);
}

CPlayerImpl::~CPlayerImpl(void)
{
	delete m_body;
	m_body = nullptr;
}

/////////////////////////////////////
////////// CPLAYER //////////////////
/////////////////////////////////////

void CPlayer::SubscribeTo(const std::string& topic, IObserver* observer)
{
	Impl(this)->m_publisher.Register(topic, observer);
}

void CPlayer::SubscribeFrom(const std::string& topic, IObserver* observer)
{
	Impl(this)->m_publisher.Deregister(topic, observer); 
}

void CPlayer::SubscribeFromAll(IObserver* observer)
{
	Impl(this)->m_publisher.Deregister(observer);
}


CPlayer::CPlayer(CGameLevel* level)
	: IEntity(level)
{
	//m_body = new CPlayerBody(this, GameLevel()->Physics()->World());
}

CPlayer::~CPlayer(void)
{

}

b2Vec2 CPlayer::Position(void) const { return Impl(this)->m_body->Position(); }

void CPlayer::SetXSpeed(float x) 
{ 
	auto impl = Impl(this);
	if (GetXSpeed() != x)
	{
		impl->m_speed.x = x; 
		impl->m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'));
	}
}

void CPlayer::SetYSpeed(float y) 
{ 
	auto impl = Impl(this);
	if (GetYSpeed() != y)
	{
		impl->m_speed.y = y; 
		impl->m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'));
	}
}

void CPlayer::SetSpeed(const b2Vec2& speed) 
{ 
	if (!(GetSpeed() == speed))
	{
		Impl(this)->m_speed = speed; 
		Impl(this)->m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('S', 'P', 'D', 'C'));
	}
}

float CPlayer::GetXSpeed(void) const { return Impl(this)->m_speed.x; }

float CPlayer::GetYSpeed(void) const { return Impl(this)->m_speed.y; }

b2Vec2 CPlayer::GetSpeed(void) const { return Impl(this)->m_speed; }

IWeapon* CPlayer::GetCurrentWeapon(void) const { return Impl(this)->m_currentWeapon; }

void CPlayer::Update(double deltaTime)
{
	auto impl = Impl(this);
	if (impl->GetCurrentWeapon())
		impl->GetCurrentWeapon()->Update(deltaTime);
	b2Body* body = impl->m_body->Raw();

	body->ApplyLinearImpulse(b2Vec2(ImpulseForDistance(impl->m_speed, body)), body->GetWorldCenter()); 
}

DIRECTION CPlayer::GetDirection(void) const
{
	return Impl(this)->m_dir;
}

void CPlayer::SetDirection(DIRECTION dir)
{
	auto impl = Impl(this);
	// Only update direction if it is a new direction
	if (impl->m_dir != dir)
	{
		impl->m_dir = dir;
		impl->m_publisher.NotifyAll(ALLEGRO_GET_EVENT_TYPE('D', 'I', 'R', 'C'));
		//impl->m_publisher.NotifyAll("DirectionChanged", new DirectionChanged(impl->m_dir));
	}
}

void CPlayer::AdvanceLevel(void)
{
	//m_publisher.NotifyAll("LevelUp", new LevelUpEvent(this, ++m_level));
}


CPlayer* VE::CreatePlayer(CGameLevel* level, const b2Vec2& spawnPos)
{
	return new CPlayerImpl(level, spawnPos);
}