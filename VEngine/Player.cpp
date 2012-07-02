#include "Player.h"
#include <iostream>
#include "PlayerBody.h"
#include "GameLevel.h"

using namespace VE;

// Calculate impulse needed to simulate moving the desiredVel over one second.
float ImpulseForDistanceX(float desiredVel, b2Body* body)
{
		b2Vec2 vel = body->GetLinearVelocity();
		float velChange = desiredVel - vel.x;
		float impulse = body->GetMass() * velChange;
		return impulse;
		//GetCharacterBody()->ApplyLinearImpulse(b2Vec2(impulse, 0), GetCharacterBody()->GetWorldCenter());
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
		CPlayerImpl(CGameLevel* level);
		~CPlayerImpl(void);

	private:
		CObservable m_publisher;
		CPlayerBody* m_body;
		b2Vec2 m_speed;
		b2Vec2 m_vel;

		bool m_movedRThisFrame;
		bool m_movedLThisFrame;
	};
}

inline CPlayerImpl* Impl(CPlayer* player) { return static_cast<CPlayerImpl*>(player); }
inline const CPlayerImpl* Impl(const CPlayer* player) { return static_cast<const CPlayerImpl*>(player); }

CPlayerImpl::CPlayerImpl(CGameLevel* level)
	: CPlayer(level)
	, m_body(nullptr)
	, m_speed(0,0)
	, m_vel(5,5)
	, m_movedRThisFrame(false)
	, m_movedLThisFrame(false)
{
	m_body = new CPlayerBody(this, GameLevel()->Physics()->World());
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

void CPlayer::SetXSpeed(float x) { Impl(this)->m_speed.x = x; }

void CPlayer::SetYSpeed(float y) { Impl(this)->m_speed.y = y; }

void CPlayer::SetSpeed(const b2Vec2& speed) { Impl(this)->m_speed = speed; }

float CPlayer::GetXSpeed(void) const { return Impl(this)->m_speed.x; }

float CPlayer::GetYSpeed(void) const { return Impl(this)->m_speed.y; }

b2Vec2 CPlayer::GetSpeed(void) const { return Impl(this)->m_speed; }


void CPlayer::MoveRight(void)
{
	CPlayerImpl* impl = Impl(this);

	if (impl->m_movedRThisFrame)
		return;

	impl->m_speed.x += impl->m_vel.x;
}

void CPlayer::MoveLeft(void)
{
	CPlayerImpl* impl = Impl(this);

	if (impl->m_movedLThisFrame)
		return;

	impl->m_speed.x -= impl->m_vel.x;
}

void CPlayer::Update(double deltaTime)
{
	CPlayerImpl* impl = Impl(this);
	b2Body* body = impl->m_body->Raw();

	body->ApplyLinearImpulse(b2Vec2(ImpulseForDistance(impl->m_speed, body)), body->GetWorldCenter()); 
	//impl->m_speed.SetZero();
}

void CPlayer::AdvanceLevel(void)
{
	//m_publisher.NotifyAll("LevelUp", new LevelUpEvent(this, ++m_level));
}


CPlayer* VE::CreatePlayer(CGameLevel* level)
{
	return new CPlayerImpl(level);
}