#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <vengine\GameObject.h>
#include <vengine\Script\LuaScript.h>
#include <memory>
#include <string>

namespace VE
{
	class CScriptObject: public NE::IGameObject
	{
	protected:
		void OnUpdate(void);

	public:
		CScriptObject(const std::string& filename);

	private:
		std::unique_ptr<CLuaScript> m_script;
	};
}
#endif