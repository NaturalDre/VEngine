#include "vengine\ObjectManager.h"
#include <vengine\GameObject.h>
#include <vengine\Animation\AnimationBase.h>
#include <algorithm>

namespace VE
{
	CObjectManager::CObjectManager(void)
	{

	}

	void CObjectManager::Logic(void)
	{
		//std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [&](NE::IGameObject* gameObj)
		//{
		//	gameObj->OnUpdate();
		//});
	}

	void CObjectManager::Cleanup(void)
	{

	}

	void CObjectManager::UpdateGameObjects(void)
	{
		std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [&](NE::IGameObject* gameObj)
		{
			gameObj->OnUpdate();
		});
	}

	void CObjectManager::UpdateAnimations(void)
	{
		std::for_each(m_animations.begin(), m_animations.end(), [&](IAnimationBase* anim)
		{
			anim->Logic();
		});
	}


	CObjectManager& GetObjMgr(void)
	{
		static CObjectManager instance;
		return instance;
	}
}