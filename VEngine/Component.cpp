#include "Component.h"
#include <luabind\luabind.hpp>
#include <luabind\wrapper_base.hpp>

namespace VE
{
	class CComponentWrapper: public IComponent, public luabind::wrap_base
	{
	public:
		void Update(double dt) { call<void>("Update", dt); }
		static void DefaultUpdate(IComponent* c, double dt) { return c->Update(dt); }
	};


	void IComponent::Export(lua_State* L)
	{
		using namespace luabind;

		module(L)
			[
				class_<IComponent, CComponentWrapper>("IComponent")
				.def(constructor<>())
				.def("Update", &CComponentWrapper::DefaultUpdate)
			];
	}
}