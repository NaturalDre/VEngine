#ifndef SCRIPTEDOBJECTMODEL_H
#define SCRIPTEDOBJECTMODEL_H

#include "ObjectModel.h"
#include "Script.h"
#include <memory>

namespace VE
{
	class CScriptedObjectModel: public IObjectModel
	{
	protected:
		void Update(void);
	public:
		CScriptedObjectModel(const char* scriptFile);
		~CScriptedObjectModel(void);

	private:
		std::unique_ptr<CScript> m_script;
	};
}
#endif