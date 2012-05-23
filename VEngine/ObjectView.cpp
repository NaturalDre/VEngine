#include "ObjectView.h"
#include "Render.h"

namespace VE
{
	IObjectView::IObjectView(int drawNum)
	{
		m_drawNumber = drawNum;
		Renderer()->Register(this);
	}

	IObjectView::~IObjectView(void)
	{
		Renderer()->Deregister(this);
	}

}