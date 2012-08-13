#include "WeaponAK47.h"
#include "BulletAK47.h"
#include "Physics.h"
#include "GameLevel.h"
#include "ErrorLogger.h"
#include <luabind\luabind.hpp>
#include <iostream>
#include <algorithm>
#include <allegro5\altime.h>

namespace VE
{
	CWeaponAK47::CWeaponAK47(CGameLevel* level, CPlayer* player)
		: IWeapon(100, 100, 1, level)
		, m_fireRate(0.1f)
		, m_fireTimeout(0)
		, m_reloadTime(1.0f)
		, m_player(player)
	{
		assert(m_player != nullptr);
		assert(GetGameLevel() != nullptr);

		if (!m_player || !GetGameLevel())
			return;

		m_self = luabind::call_function<luabind::object>(GetGameLevel()->GetScriptEnv(), "Script_AK", this);
		m_bulletImage = CBitmap("Images/bulletm.png");
	}

	CWeaponAK47::~CWeaponAK47(void)
	{
		FreeFinishedBullets();
		FreeFiredBullets();
		m_player = nullptr;
	}

	void CWeaponAK47::Update(double dt)
	{
		FreeFinishedBullets();

		if (GetState() == e_Reloading && m_reloadTimeout <= 0)
			SetState(e_Ready);

		if (m_fireTimeout > 0)
			m_fireTimeout -=  dt;

	}

	void CWeaponAK47::Render(void)
	{
		std::for_each(m_firedBullets.begin(), m_firedBullets.end(), [&](CBulletAK47* bullet)
		{
			VE::DrawBitmap(m_bulletImage, bullet->GetBody()->GetPosition());
		});
	}

	void CWeaponAK47::FreeFiredBullets(void)
	{
		std::for_each(m_firedBullets.begin(), m_firedBullets.end(), [&](IProjectile* bullet)
		{
			delete bullet;
		});
		m_firedBullets.clear();
	}

	void CWeaponAK47::FreeFinishedBullets(void)
	{
		for (auto iter = m_firedBullets.begin(); iter != m_firedBullets.end(); ++iter)
		{
			CBulletAK47* bullet = *iter;
			if (bullet->IsDone())
			{
				delete bullet;
				iter = m_firedBullets.erase(iter);
				if (iter == m_firedBullets.end())
					break;
			}
		}
	}

	void CWeaponAK47::CallScriptFunc(const std::string& function)
	{
		if (m_self.is_valid())
		{
			try { luabind::call_member<void>(m_self, function.c_str()); }
			catch(const luabind::error& e)
			{
				if (GetGameLevel()->GetLogger())
					GetGameLevel()->GetLogger()->LogError("CWeaponAK47::CallScriptFunc() with parameter value " + function + " generated error: " + lua_tostring(e.state(), -1));
				lua_pop(e.state(), 1);
			}
		}
	}

	void CWeaponAK47::Fire(const b2Vec2& pos)
	{
		if (!CanFire())
			return;

		m_fireTimeout = m_fireRate;
		CBulletAK47* bullet(new CBulletAK47(GetGameLevel()->GetPhysics()->World(), this, pos));
		m_firedBullets.push_back(bullet);
		SetAmmo(GetAmmoCount() -1);
		CallScriptFunc("OnFire");

	}

	void CWeaponAK47::Reload(void)
	{
		if (GetState() == e_Reloading)
			return;
		else 
			SetState(e_Reloading);
		CallScriptFunc("OnReload");
	}
}