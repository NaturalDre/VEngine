#include <vengine\Character\Character.h>

namespace VE
{
	ICharacter::ICharacter(void)
		: m_health(100.0f)
		, m_exp(0)
		, m_moveSpeed(5,0)
		, m_maxVel(5, 5)
		, m_moveBy(0,0)
	{

	}

	ICharacter::~ICharacter(void)
	{

	}

	void ICharacter::MoveX(float desiredVel)
	{
		b2Vec2 vel = GetBody()->GetLinearVelocity();
		float velChange = desiredVel - vel.x;
		float impulse = GetBody()->GetMass() * velChange;
		GetBody()->ApplyLinearImpulse(b2Vec2(impulse, 0), GetBody()->GetWorldCenter());
	}
}