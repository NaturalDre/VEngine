#include "ObjectModel.h"
#include "ObjectManager.h"

namespace VE
{
	IObjectModel::IObjectModel(void)
	{
		ObjectMgr()->Register(this);
	}

	IObjectModel::~IObjectModel(void)
	{
		ObjectMgr()->Deregister(this);
	}
}