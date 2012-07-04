#ifndef BULLET_AK47_H
#define BULLET_AK47_H

#include "Bullet.h"
#include "Physics.h"
#include "Constants.h"

namespace VE
{
	class Weapon_AK47;
	class Bullet_AK47: public IBullet
	{
	protected:
		void BeginContact(b2Contact* contact);
		void Destroy(void);

	public:
		Bullet_AK47(b2World* world, Weapon_AK47* weapon, const Direction dir);
		~Bullet_AK47(void);

	private:
		b2Body* m_body;
		Weapon_AK47* m_weapon;
	};
}
#endif