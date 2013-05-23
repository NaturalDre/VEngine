#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <vector>
#include <luabind\object.hpp>
#include "Asset.h"

struct lua_State;

namespace VE
{
	luabind::object GetFactory(lua_State* L, const std::string& factory);
	class CScript//: public IAsset
	{
	protected:

	public:
		CScript(lua_State* state, const std::string& scriptName);
		CScript(const luabind::adl::object& scriptObject);

		~CScript(void);

		const luabind::adl::object& GetSelf(void) const { return m_self; }

		bool IsValid(void) const { return m_self.is_valid(); }
		
		void Update(double dt);

		luabind::object operator[](const std::string& member);

		static void Export(lua_State* L);
	private:
		std::vector<char> m_buffer;
		luabind::object m_self;
	};
}
#endif