#include "LuabindExport.h"
#include <luabind\luabind.hpp>
#include "Script.h"
#include "RigidBody.h"

using namespace luabind;
using namespace VE;

void ExportBindings(lua_State* L)
{
	luabind::module(L)
		[
			class_<CScript>("Script")
			.def(constructor<const object&>())
		];

	luabind::module(L)
		[
			class_<CRigidBody>("RigidBody")
			.def(constructor<const object&>())
			.def("Free", &CRigidBody::Free)
		];
}