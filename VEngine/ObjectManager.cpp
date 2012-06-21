#include "ObjectManager.h"
#include <algorithm>
#include "GameObject.h"

namespace VE
{
	CObjectManager* OBJMGR = nullptr;

	CObjectManager::CObjectManager(void)
	{
		assert(OBJMGR == nullptr);
		OBJMGR = this;
	}

	CObjectManager::~CObjectManager(void)
	{
		OBJMGR = nullptr;	
	}

	void CObjectManager::UpdateGameObjects(void)
	{
		for (auto iter = m_objectModels.begin(); iter != m_objectModels.end(); ++iter)
			(*iter)->Update();
	}
	IGameObject* CObjectManager::FindGameObject(const std::string& tag) const
	{
		for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
		{
			if ((*iter)->Tag() == tag)
				return *iter;
		}
		return nullptr;
	}

	bool CObjectManager::GameObjectExists(IGameObject* gameObj) const
	{
		auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObj);
		if (iter != m_gameObjects.end())
			return true;
		return false;
	}


	CObjectManager* ObjectMgr(void)
	{
		if (!OBJMGR)
			OBJMGR = new CObjectManager;
		return OBJMGR;
	}
}