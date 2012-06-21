#include "Script.h"
#include <lauxlib.h>
#include <assert.h>
#include <boost\lexical_cast.hpp>
#include "Utility.h"
#include "Application.h"

namespace VE
{
	CScript::CScript(const char* scriptFile)
		: m_scriptFile(scriptFile)
	{
		m_id = std::string("script_") + boost::lexical_cast<std::string>(this);
		m_buffer = FileToBuffer(scriptFile);
		assert(m_buffer.empty() != true);
		//m_state = lua_open();
		//assert(m_state != nullptr);
		//luaL_dofile(m_state, scriptFile);
	}

	CScript::~CScript(void)
	{
		//lua_close(m_state);
		//m_state = nullptr;
	}

	void CScript::Init(void)
	{
		if (luaL_loadbuffer(App()->LuaState(), m_buffer.data(), m_buffer.size(), nullptr))
		{
			const char* error = lua_tostring(App()->LuaState(), -1);
			lua_pop(App()->LuaState(), 1);

			LuaError lerr(m_scriptFile);
			//lerr.Error() << error << "\n\n" << __FILE__ << "\n\n" << __LINE__;
			throw(lerr);
			//throw(std::exception((std::string(error) + "\n\n" + __FILE__ + "\n\n" + m_scriptFile).c_str()));
		}
	}

	void CScript::Update(void)
	{

	}
}