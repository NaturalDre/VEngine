#ifndef GAMEOBJECTLIST_H
#define GAMEOBJECTLIST_H

#include <list>

class IGameObject;

namespace VE
{
	class CGameObjectList
	{
	private:
		std::list<IGameObject> m_gameObjects;
	};
}
#endif