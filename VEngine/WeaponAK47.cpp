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
		: IWeapon(100, 100, 1, nullptr)
		, m_fireRate(0.1f)
		, m_fireTimeout(0)
		, m_reloadTime(1.0f)
		, m_gameLevel(level)
		, m_player(player)
	{
		assert(m_player != nullptr);
		assert(m_gameLevel != nullptr);

		if (!m_player || !m_gameLevel)
			return;

		m_self = luabind::call_function<luabind::object>(m_gameLevel->GetScriptEnv(), "Script_AK", this);
		m_bulletImage = CBitmap("Images/bulletm.png");
	}

	CWeaponAK47::~CWeaponAK47(void)
	{
		FreeFinishedBullets();
		FreeFiredBullets();
		m_player = nullptr;
		m_gameLevel = nullptr;
	}

	void CWeaponAK47::Update(double dt)
	{
		ForceFinishOldBullets();
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

	void CWeaponAK47::ForceFinishOldBullets(void)
	{
		const double curTime = al_get_time();

		for (auto iter = m_firedBullets.begin(); iter != m_firedBullets.end(); ++iter)
		{
			if (curTime - (*iter)->GetTimeCreated() > 1)
			{
				m_finishedBullets.push_back(*iter);
				iter = m_firedBullets.erase(iter);
				if (iter == m_firedBullets.end())
					break;
			}
		};
	}

	void CWeaponAK47::FreeFinishedBullets(void)
	{
		std::for_each(m_finishedBullets.begin(), m_finishedBullets.end(), [&](IProjectile* bullet)
		{
			delete bullet;
		});
		m_finishedBullets.clear();
	}

	void CWeaponAK47::Done(CBulletAK47* bullet)
	{
		/*CBulletAK47* b = static_cast<CBulletAK47*>(bullet);*/
		m_finishedBullets.push_back(bullet);
		m_firedBullets.remove(bullet);
	}

	void CWeaponAK47::CallScriptFunc(const std::string& function)
	{
		if (m_self.is_valid())
		{
			try { luabind::call_member<void>(m_self, function.c_str()); }
			catch(const luabind::error& e)
			{
				if (m_gameLevel->GetLogger())
					m_gameLevel->GetLogger()->LogError("CWeaponAK47::CallScriptFunc() with parameter value " + function + " generated error: " + lua_tostring(e.state(), -1));
				lua_pop(e.state(), 1);
			}
		}
	}

	void CWeaponAK47::Fire(const b2Vec2& pos)
	{
		if (!CanFire())
			return;

		m_fireTimeout = m_fireRate;
		CBulletAK47* bullet(new CBulletAK47(m_gameLevel->Physics()->World(), this, pos));
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