#include "ScriptedObjectModel.h"
#include "Utility.h"

namespace VE
{
	CScriptedObjectModel::CScriptedObjectModel(const char* scriptFile)
	{
		m_script.reset(new CScript(scriptFile));
		try { m_script->Init(); } catch(const LuaError& e)
		{
			vWarning(e.what());
		}
	}

	CScriptedObjectModel::~CScriptedObjectModel(void)
	{
		m_script.reset();
	}

	void CScriptedObjectModel::Update(void)
	{
		if (m_script)
			m_script->Update();
	}
}