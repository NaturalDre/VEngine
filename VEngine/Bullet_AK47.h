#ifndef BULLET_AK47_H
#define BULLET_AK47_H

#include "Bullet.h"
#include "Physics.h"
#include "Common.h"
#include "ContactCallback.h"
namespace VE
{
	class Weapon_AK47;
	class Bullet_AK47: private IContactCallback, public IBullet
	{
		friend Weapon_AK47;
	protected:
		void BeginContact(b2Contact* contact);
		void Destroy(void);

	public:
		Bullet_AK47(b2World* world, Weapon_AK47* weapon, const DIRECTION dir);
		virtual ~Bullet_AK47(void);

		inline b2Body* GetBody(void) const { return m_body; }
		inline double GetTimeCreated(void) const { return m_timeCreated; }
	private:
		b2World* m_world;
		b2Body* m_body;
		Weapon_AK47* m_weapon;
		double m_timeCreated;
	};
}
#endif