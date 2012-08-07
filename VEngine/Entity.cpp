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

	IEntity::~IEntity(void)
	{
		if (m_gameLevel)
			m_gameLevel->RemoveEntity(this);
	}
	void IEntity::Update(double deltaTime)
	{
		m_script->Update(deltaTime);
	}
}