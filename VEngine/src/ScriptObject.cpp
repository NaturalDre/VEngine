#include <vengine\Script\ScriptObject.h>
#include <vengine\Script\Script.h>

namespace VE
{
	CScriptObject::CScriptObject(const std::string& filename)
	{
		m_script.reset(GetScriptMgr().LoadScript(filename));
	}

	void CScriptObject::OnUpdate(void)
	{
		if (m_script)
			m_script->CallUpdate();
	}
}