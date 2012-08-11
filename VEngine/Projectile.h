#ifndef BULLET_H
#define BULLET_H

#include <Box2D\Common\b2Math.h>

namespace VE
{
	class IProjectile
	{
	protected:
		inline void SetDamage(float damage) { m_damage = damage; }

	public:
		virtual ~IProjectile(void) = 0 { }

		inline float GetDamage(void) { return m_damage; }
		virtual b2Vec2 GetLinearVelocity(void) const { return b2Vec2(0,0); }

	private:
		float m_damage;
	};
}
#endif