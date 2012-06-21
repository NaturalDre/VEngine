#include "GameObject.h"
#include "ObjectManager.h"

namespace VE
{
	IGameObject::IGameObject(void)
	{
		ObjectMgr()->Register(this);
	}

	IGameObject::~IGameObject(void)
	{
		ObjectMgr()->Deregister(this);
	}
}