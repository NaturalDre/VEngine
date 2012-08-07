#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <vector>
#include <luabind\object.hpp>

struct lua_State;

//#ifndef CALLSCRIPTFUNCTION
//#define CALLSCRIPTFUNCTION
//#define CallFunction luabind::call_function<luabind::object>
//#endif

namespace VE
{
	luabind::object GetFactory(lua_State* L, const std::string& factory);
	class CScript
	{
	protected:

	public:
		CScript(const std::string& scriptName);
		CScript(const luabind::adl::object& scriptObject);

		~CScript(void);

		const luabind::adl::object& GetSelf(void) const { return m_self; }

		bool IsValid(void) const { return m_self.is_valid(); }
		
		void Update(double dt);
		//void Render(void);
	private:
		std::vector<char> m_buffer;
		luabind::adl::object m_self;
	};
}
#endif