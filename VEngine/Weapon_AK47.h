#ifndef WEAPON_AK47_H
#define WEAPON_AK47_H

#include "Weapon.h"
#include "Bullet_AK47.h"
#include <list>
#include <memory>

namespace VE
{
	//typedef std::unique_ptr<Bullet_AK47> pAK47Bullet;
	//typedef Bullet_AK47* pAK47Bullet;
	//class CGameLevel;
	class CPlayer;
	class CPhysics;
	class Weapon_AK47: public IWeapon
	{
	protected:
		void Update(double dt);


	public:
		Weapon_AK47(CPhysics* physics, CPlayer* player);
		~Weapon_AK47(void);

		void Fire(Direction dir);
		void Reload(void);
		void Done(IBullet* bullet);
		/// \return The player that is using this weapon.
		CPlayer* Player(void) const { return m_player; }
	private:
		std::list<Bullet_AK47*> m_firedBullets;
		std::list<IBullet*> m_finishedBullets;
		CPhysics* m_physics;
		CPlayer* m_player;
		/// How long to wait 'til the weapon can be fired again
		double m_fireRate; 
		double m_fireTimeout;
		double m_reloadTime;
		double m_reloadTimeout;
	};
}

#endif