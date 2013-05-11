#include "PhysicsEntity.h"
#include <luabind\luabind.hpp>
namespace VE
{
	void IPhysicsEntity::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<IPhysicsEntity, IEntity>("IPhysicsEntity")
			];
	}
}