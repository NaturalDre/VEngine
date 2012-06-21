#include "Render.h"
#include "View.h"
#include "TMR\MapFile.h"
#include <algorithm>

namespace VE
{
	CRender::CRender(void)
		: m_mapFile(nullptr)
	{
		m_mapFile = new Tiled::CMapFile;
	}

	CRender::~CRender(void)
	{

	}

	void CRender::AddView(IView* view)
	{
		if (view == nullptr)
			return;

		auto iter = std::find(m_views.begin(), m_views.end(), view);
		if (iter == m_views.end())
			m_views.push_back(view);
	}

	void CRender::RemoveView(IView* view)
	{
		auto iter = std::find(m_views.begin(), m_views.end(), view);
		if (iter != m_views.end())
			m_views.erase(iter);
	}

	void CRender::Render(void)
	{
		// TO DO: Draw map


		std::sort(m_views.begin(), m_views.end(), [](IView* lhs, IView* rhs)
		{
			return lhs->DrawOrder() < rhs->DrawOrder();
		});

		for (auto iter = m_views.begin(); iter != m_views.end(); ++iter)
			(*iter)->Draw();
	}
}