#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <vector>
#include <luabind\object.hpp>

struct lua_State;

#define Call_Func luabind::call_function<luabind::object>

namespace VE
{
	luabind::object GetFactory(lua_State* L, const std::string& factory);
	class CScript
	{
	protected:


	public:
		//CScript(lua_State* L, const std::string& factoryFunc);
		CScript(const luabind::adl::object& obj);

		~CScript(void);

		const luabind::adl::object GetSelf(void) const { return m_self; }

		bool IsValid(void) const { return m_self.is_valid(); }

		void Update(double dt);
		void Render(void);
	private:
		std::vector<char> m_buffer;
		luabind::adl::object m_self;
	};
}
#endif