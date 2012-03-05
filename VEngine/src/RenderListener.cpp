//#include "vengine\Render\RenderListener.h"
#include "vengine\Render\Render.h"

namespace VE
{
	IRenderListener::IRenderListener(size_t orderID)
		: m_orderID(orderID)
	{
		// Add to manager so it can tell us when it's time to draw
		GetRenderMgr().AddListener(this);
	}

	IRenderListener::~IRenderListener(void)
	{
		// Remove from the manager so it doesn't try dereferencing an invalid pointer.
		GetRenderMgr().RemoveListener(this);
	}
}