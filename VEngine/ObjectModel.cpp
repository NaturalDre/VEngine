#include "ObjectModel.h"
#include "Application.h"

namespace VE
{

	IObjectModel::IObjectModel(void)
	{
		Internal::Register(this);
	}

	IObjectModel::~IObjectModel(void)
	{
		Internal::Deregister(this);
	}
}