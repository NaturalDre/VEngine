#include "vengine\Level\Level.h"
#include <vengine\ObjectManager.h>
#include <vengine\Render\Render.h>

namespace VE
{
	CLevelManager::CLevelManager(void)
	{

	}

	void CLevelManager::Cleanup(void)
	{
		UnloadCurrentLevel();
		m_levelLoader.reset();
		
	}

	void CLevelManager::Logic(void)
	{
		if (m_levelLoader)
			m_levelLoader->Logic();
	}

	void CLevelManager::LoadLevel(const std::string& filename)
	{
		if(!m_levelLoader)
			return;
		UnloadCurrentLevel();
		m_levelLoader->LoadLevel(filename);
	}

	void CLevelManager::UnloadCurrentLevel(void)
	{
		if (!m_levelLoader)
			return;

		m_levelLoader->UnloadCurrentLevel();
		m_gameObjects.clear();
		m_bodies.clear();
		GetObjMgr().SetPlayer(nullptr);
		GetRenderMgr().GetCam()->SetTarget(nullptr);
		

	}

	CLevelManager& GetLvlMgr(void)
	{
		static CLevelManager instance;
		return instance;
	}
};