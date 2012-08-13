#ifndef BULLET_AK47_H
#define BULLET_AK47_H

#include "Projectile.h"
#include "Physics.h"
#include "Common.h"
#include "ContactCallback.h"

namespace VE
{
	class CWeaponAK47;
	class CBulletAK47: private IContactCallback, public IProjectile
	{
		friend CWeaponAK47;
	protected:
		void BeginContact(b2Contact* contact);
		void Destroy(void);

	public:
		CBulletAK47(b2World* world, CWeaponAK47* weapon, const b2Vec2& pos);
		virtual ~CBulletAK47(void);

		inline b2Body* GetBody(void) const { return m_body; }
		inline double GetTimeCreated(void) const { return m_timeCreated; }
		inline bool IsDone(void) { return m_done; }
	private:
		b2World* m_world;
		b2Body* m_body;
		CWeaponAK47* m_weapon;
		double m_timeCreated;
		bool m_done;
	};
}
#endif