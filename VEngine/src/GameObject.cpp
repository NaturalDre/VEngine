#include "vengine\GameObject.h"
#include <vengine\Script\LuaScript.h>
#include <vengine\ObjectManager.h>

using namespace NE;

namespace NE
{
	IGameObject::IGameObject(const std::string& tag)
	{
		// TO DO: Add to object manager
		VE::GetObjMgr().Add(this);
	}

	IGameObject::~IGameObject(void)
	{
		// TO DO: Remove from object manager
		VE::GetObjMgr().Remove(this);
	}
}