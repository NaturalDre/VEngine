#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "Common.h"

struct ALLEGRO_BITMAP;

namespace VE
{
	class IBullet;
	class IWeapon: public IEntity
	{
		friend IBullet;
	public:
		enum WeaponState { e_Ready, e_Reloading };

	protected:
		IWeapon(size_t ammo = 0, size_t maxAmmo = 0, size_t rarity = 1, CGameLevel* level = nullptr)
			: IEntity(level)
			, m_ammo(ammo)
			, m_maxAmmo(maxAmmo)
			, m_rarity(rarity)
			, m_state(e_Ready)
		{}
		/// Bullet's that are fired by this weapon should 
		/// call this function when they need to be destroyed.
		/// For example: When they have done damage or have been
		/// alive for too long. They are deleted in the next Update() call.
		///
		/// @param bullet The bullet that is done doing its job.
		/// \note Do not delete the bullet before this function returns;
		virtual void Done(IBullet* bullet) = 0;


		void SetAmmo(size_t ammo) { m_ammo = ammo; }
		void SetMaxAmmo(size_t maxAmmo) { m_maxAmmo; }
		void SetRarity(size_t rarity) { m_rarity = rarity; }
		void SetState(WeaponState state) { m_state = state; }
		void SetWeaponID(int weaponID) { m_weaponID = weaponID; }

	public:
		virtual ~IWeapon(void) { }

		virtual void Update(double dt) = 0;
		virtual void Render(void) = 0;
		/// Fire a bullet from the weapon.
		/// \note Derived classes should handle whether or not
		///		the weapon can be fired.
		virtual void Fire(DIRECTION dir) = 0;
		/// Reload this weapon.
		/// \note Derived classes should handle whether or not
		///		the weapon can be reloaded.
		virtual void Reload(void) = 0;
		inline int GetAmmoCount(void) const { return m_ammo; }
		inline int GetMaxAmmo(void) const { return m_maxAmmo; }
		/// How rare the weapon's ammo is.
		/// \note The rarity determines how much ammo this weapon will get
		///		when an ammo pack is picked up. e.g., if an ammo pack contains
		///		5 ammo and this weapon's rarity is 2, then it will get 10 (5*2)
		///		ammo from the ammo pack.
		inline int GetRarity(void) const { return m_rarity; }
		/// \return A numeric id representing this specific weapon.
		/// \note This is meant to be used if some code ever needs
		/// to know the exact weapon this is. Try not to use the 
		/// same ID twice. (I'll try to find a better way to do this.)
		inline int GetWeaponID(void) const { return m_weaponID; }
		/// \return An enum representing the state of this weapon. 
		/// @see IWeapon::WeaponState
		inline WeaponState GetState(void) const { return m_state; }
		/// Icon of the weapon to be used with the GUI.
		virtual ALLEGRO_BITMAP* GetIcon(void) const { return nullptr; }


	private:
		size_t m_ammo;
		size_t m_rarity;
		size_t m_maxAmmo;
		int m_weaponID;

		WeaponState m_state;

	};
}
#endif