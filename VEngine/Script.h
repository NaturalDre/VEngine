#ifndef SCRIPT_H
#define SCRIPT_H

#include <lua.hpp>
#include <string>
#include <vector>
#include "LuaError.h"

namespace VE
{
	class CScript
	{
	protected:

	public:
		CScript(const char* scriptFile);
		~CScript(void);

		void Init(void);
		void Reload(void);
		void Update(void);
		//lua_State* State(void) const { return m_state; }

	private:
		std::string m_id;
		std::string m_scriptFile;
		std::vector<char> m_buffer;
		//lua_State* m_state;
	};
}
#endif