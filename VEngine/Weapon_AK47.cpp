#include "Weapon_AK47.h"
#include "Bullet_AK47.h"
#include "Physics.h"
#include "GameLevel.h"
#include "ErrorLogger.h"
#include <luabind\luabind.hpp>
#include <iostream>
#include <algorithm>
#include <allegro5\altime.h>

namespace VE
{
	Weapon_AK47::Weapon_AK47(CGameLevel* level, CPlayer* player)
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

	Weapon_AK47::~Weapon_AK47(void)
	{
		FreeFinishedBullets();
		FreeFiredBullets();
		m_player = nullptr;
		m_gameLevel = nullptr;
	}

	void Weapon_AK47::Update(double dt)
	{
		ForceFinishOldBullets();
		FreeFinishedBullets();

		if (GetState() == e_Reloading && m_reloadTimeout <= 0)
			SetState(e_Ready);

		if (m_fireTimeout > 0)
			m_fireTimeout -=  dt;

	}

	void Weapon_AK47::Render(void)
	{
		std::for_each(m_firedBullets.begin(), m_firedBullets.end(), [&](Bullet_AK47* bullet)
		{
			VE::DrawBitmap(m_bulletImage, bullet->GetBody()->GetPosition());
		});
	}

	void Weapon_AK47::FreeFiredBullets(void)
	{
		std::for_each(m_firedBullets.begin(), m_firedBullets.end(), [&](IBullet* bullet)
		{
			delete bullet;
		});
		m_firedBullets.clear();
	}

	void Weapon_AK47::ForceFinishOldBullets(void)
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

	void Weapon_AK47::FreeFinishedBullets(void)
	{
		std::for_each(m_finishedBullets.begin(), m_finishedBullets.end(), [&](IBullet* bullet)
		{
			delete bullet;
		});
		m_finishedBullets.clear();
	}

	void Weapon_AK47::Done(IBullet* bullet)
	{
		Bullet_AK47* b = static_cast<Bullet_AK47*>(bullet);
		m_finishedBullets.push_back(b);
		m_firedBullets.remove(b);
	}

	void Weapon_AK47::CallScriptFunc(const std::string& function)
	{
		if (m_self.is_valid())
		{
			try { luabind::call_member<void>(m_self, function.c_str()); }
			catch(const luabind::error& e)
			{
				if (m_gameLevel->GetLogger())
					m_gameLevel->GetLogger()->LogError("Weapon_AK47::CallScriptFunc() with parameter value " + function + " generated error: " + lua_tostring(e.state(), -1));
				lua_pop(e.state(), 1);
			}
		}
	}

	void Weapon_AK47::Fire(DIRECTION dir)
	{
		if (m_fireTimeout > 0 || GetAmmoCount() <= 0)
			return;

		m_fireTimeout = m_fireRate;

		Bullet_AK47* bullet(new Bullet_AK47(m_gameLevel->Physics()->World(), this, dir));
		m_firedBullets.push_back(bullet);

		SetAmmo(GetAmmoCount() - 1);

		CallScriptFunc("OnFire");
	}

	void Weapon_AK47::Reload(void)
	{
		if (GetState() == e_Reloading)
			return;
		else 
			SetState(e_Reloading);
		CallScriptFunc("OnReload");
	}
}