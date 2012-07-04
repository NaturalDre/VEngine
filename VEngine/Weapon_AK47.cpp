#include "Weapon_AK47.h"
#include "Bullet_AK47.h"
#include "Physics.h"
#include <iostream>
#include <algorithm>

namespace VE
{
	Weapon_AK47::Weapon_AK47(CPhysics* physics, CPlayer* player)
		: IWeapon(100, 100, 1, nullptr)
		, m_fireRate(0.1f)
		, m_fireTimeout(0)
		, m_physics(physics)
		, m_player(player)
	{
		assert(m_player != nullptr);
	}

	Weapon_AK47::~Weapon_AK47(void)
	{
		m_player = nullptr;
	}

	void Weapon_AK47::Update(double dt)
	{
		std::for_each(m_finishedBullets.begin(), m_finishedBullets.end(), [&](IBullet* bullet)
		{
			delete bullet;
		});
		m_finishedBullets.clear();

		if (GetState() == e_Reloading && m_reloadTimeout <= 0)
			SetState(e_Ready);

		if (m_fireTimeout > 0)
			m_fireTimeout -=  dt;

	}

	void Weapon_AK47::Done(IBullet* done)
	{
		m_finishedBullets.push_back(done);
	}

	void Weapon_AK47::Fire(Direction dir)
	{
		if (m_fireTimeout > 0 || GetAmmoCount() <= 0)
			return;

		m_fireTimeout = m_fireRate;

		Bullet_AK47* bullet(new Bullet_AK47(m_physics->World(), this, dir));
		m_firedBullets.push_back(std::move(bullet));

		SetAmmo(GetAmmoCount() - 1);
		std::cout << std::endl << "AK47 Fired. ";
		std::cout << std::endl << "Current Ammo:" << GetAmmoCount();
	}

	void Weapon_AK47::Reload(void)
	{
		if (GetState() == e_Reloading)
			return;
		else 
			SetState(e_Reloading);

		std::cout << std::endl << "AK47 Reloaded.";
	}
}