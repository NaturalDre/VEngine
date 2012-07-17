#include "Entity.h"
#include "Script.h"
#include "GameLevel.h"

namespace VE
{
	IEntity::IEntity(CGameLevel* level): m_gameLevel(level) 
	{
		if (m_gameLevel)
			m_gameLevel->AddEntity(this);
	}

	void IEntity::Update(double deltaTime)
	{
		for (auto iter = m_scripts.begin(); iter != m_scripts.end(); ++iter)
		{
			(*iter)->Update(deltaTime);
		}
	}
}