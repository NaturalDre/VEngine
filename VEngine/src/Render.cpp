#include "vengine\Render\Render.h"
#include "vengine\Utility.h"
#include "vengine\GUI\GUI.h"
#include <vengine\Physics.h>

#include <algorithm>

namespace VE
{
	namespace Global
	{
		const float FPS(60.0f);
	}

	bool IsLessThan(const IRenderListener* lhs, const IRenderListener* rhs)
	{
		return lhs->GetOrderID() < rhs->GetOrderID();
	}

	CRenderManager::CRenderManager(void)
	{

	};
	

	int CRenderManager::Init(size_t width, size_t height)
	{
		// Initialized Allegro game library. This should already have been
		// initialized by CApplication, but I'm playing it safe for future
		// modifications.
		if (!al_init())
		{
			Utility::ReportError("Failed to initialize Allegro in Render.cpp");
			return -1;
		}

		al_set_new_display_flags(ALLEGRO_OPENGL);
		al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
		al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_REQUIRE);

		// Create the display.
		m_display.reset(al_create_display(width, height));
		if (!m_display)
			return -1;


		SetCamera(new CCamera(std::shared_ptr<NE::IGameObject>(), al_get_display_width(al_get_current_display()), al_get_display_height(al_get_current_display())));
		return 0;
	}

	void CRenderManager::Logic(void)
	{

	}
	 
	void CRenderManager::SortListeners(void)
	{
		
	}

	void CRenderManager::Render(void)
	{
		// Clear the display
		al_clear_to_color(al_map_rgb(21,215, 98));

		// Sort from least to greatest. 
		m_listeners.sort(IsLessThan);
		// Now draw starting from the begining.
		std::for_each(m_listeners.begin(), m_listeners.end(), [&](IRenderListener* listener)
		{
			listener->Draw();
		});
		GetPhysMgr().DrawDebugData();

		GetGUIMgr().Draw();
		// Update the screen.
		al_flip_display();
	}

	void CRenderManager::Cleanup(void)
	{
		m_display.reset();
	}

	CRenderManager& GetRenderMgr(void)
	{
		static CRenderManager instance;
		return instance;
	}
};