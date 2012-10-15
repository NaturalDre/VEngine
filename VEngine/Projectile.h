#ifndef BULLET_H
#define BULLET_H

#include <Box2D\Common\b2Math.h>

struct lua_State;

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

		static void Export(lua_State* L);
	private:
		float m_damage;
	};
}
#endif