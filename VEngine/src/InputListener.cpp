#include "vengine\InputListener.h"

#include "vengine\Input.h"
namespace VE
{
	IInputListener::IInputListener(void)
	{
		GetInputMgr().AddListener(this);
	}

	IInputListener::~IInputListener(void)
	{
		GetInputMgr().RemoveListener(this);
	}
}