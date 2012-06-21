#include "View.h"
#include "Render.h"

namespace VE
{
	IView::IView(CRender* renderer, int drawOrder)
		: m_drawOrder(drawOrder)
		, m_renderer(renderer)
	{
		if (m_renderer)
			m_renderer->AddView(this);
	}

	IView::~IView(void)
	{
		if (m_renderer)
			m_renderer->RemoveView(this);
	}
}