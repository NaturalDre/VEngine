#include "Render.h"
#include "View.h"
#include "GameMap.h"
#include "Bitmap.h"
#include <algorithm>
#include <allegro5\allegro5.h>

namespace VE
{
	CRender::CRender(void)
		: IProcess(nullptr)
		, m_gameMap(nullptr)
		, m_camera(nullptr)
		, m_physics(nullptr)
		, m_uiCanvas(nullptr)
	{
		m_camera = new CCamera(nullptr, GetDisplayWidth(), GetDisplayHeight());
	}

	CRender::~CRender(void)
	{
		delete m_camera;
		m_camera = nullptr;
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
		if (!m_camera)
			return;

		// Draw map
		if (m_gameMap && m_gameMap->IsValid())
			m_gameMap->Render(this, 0, m_gameMap->GetPlayerLayer());

		std::sort(m_views.begin(), m_views.end(), [](IView* lhs, IView* rhs)
		{
			return lhs->DrawOrder() < rhs->DrawOrder();
		});

		for (auto iter = m_views.begin(); iter != m_views.end(); ++iter)
			(*iter)->Draw();

		if (m_gameMap)
			m_gameMap->Render(this, m_gameMap->GetPlayerLayer() + 1, m_gameMap->GetTileLayers().size());
		
		if (m_physics)
			m_physics->DrawDebugData();

		if (m_uiCanvas)
			m_uiCanvas->RenderCanvas();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));

	}

	size_t GetDisplayWidth(void)
	{
		return al_get_display_width(al_get_current_display());
	}

	size_t GetDisplayHeight(void)
	{
		return al_get_display_height(al_get_current_display());
	}
}