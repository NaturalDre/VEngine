#include "vengine\Level\Level.h"

namespace VE
{
	CLevelManager::CLevelManager(void)
	{

	}

	void CLevelManager::Cleanup(void)
	{
		m_levelLoader.reset();
	}

	void CLevelManager::Logic(void)
	{
		if (m_levelLoader)
			m_levelLoader->Logic();
	}

	CLevelManager& GetLvlMgr(void)
	{
		static CLevelManager instance;
		return instance;
	}
};