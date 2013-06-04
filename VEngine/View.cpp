#include "View.h"
#include "Render.h"
#include "Locator.h"

namespace VE
{
	IView::IView(int drawOrder)
		: m_drawOrder(drawOrder)
	{
		CLocator::GetRenderer()->AddView(this);
	}

	IView::~IView(void)
	{
		CLocator::GetRenderer()->RemoveView(this);
	}
}