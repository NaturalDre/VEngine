#ifndef WEAPON_AK47_H
#define WEAPON_AK47_H

#include "Weapon.h"
#include "Bitmap.h"
#include <list>
#include <memory>
#include <luabind\object.hpp>

namespace VE
{
	class CBulletAK47;
	class CPlayer;
	class CGameLevel;
	class CWeaponAK47: public IWeapon
	{
		friend CBulletAK47;
	protected:
		void Update(double dt);
		void Render(void);

		//void ForceFinishOldBullets(void);

		void FreeFiredBullets(void);
		void FreeFinishedBullets(void);

		bool CanFire(void) const { return (m_fireTimeout <= 0 && GetAmmoCount() > 0); }
		/// Bullets that his weapon shoots(aka created) should call this 
		/// when they are 'done'. Being done will usually mean the
		/// bullet has hit something and now needs to be removed
		/// from the world.
		//void Done(CBulletAK47* bullet);
		void CallScriptFunc(const std::string& function);
	public:
		CWeaponAK47(CGameLevel* level, CPlayer* player);
		~CWeaponAK47(void);

		void Fire(const b2Vec2& pos);
		void Reload(void);

		/// \return The player that is using this weapon.
		CPlayer* GetPlayer(void) const { return m_player; }
		static void Export(lua_State* L);
	private:
		std::list<CBulletAK47*> m_firedBullets;
		//std::list<IProjectile*> m_finishedBullets;
		CBitmap m_bulletImage;
		//CGameLevel* m_gameLevel; /// We do not own what this points to.
		CPlayer* m_player;	/// We do not own what this points to.
		luabind::object m_self;
		const double m_fireRate; /// How long to wait 'til the weapon can be fired again
		double m_fireTimeout;
		const double m_reloadTime;
		double m_reloadTimeout;
	};
}

#endif