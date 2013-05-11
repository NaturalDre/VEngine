#include "ContactCallback.h"
#include <luabind\luabind.hpp>

namespace VE
{
	void IContactCallback::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<IContactCallback>("IContactCallback")
			];
	}
}