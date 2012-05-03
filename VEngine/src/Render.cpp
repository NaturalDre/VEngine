#include "vengine\Render\Render.h"
#include "vengine\Utility.h"
#include <vengine\Physics.h>
#include <vengine\GUI\VengineGUI.h>
#include <algorithm>

namespace VE
{
	namespace Global
	{
		const float FPS(60.0f);
	}

	inline bool IsLessThan(const IRenderListener* lhs, const IRenderListener* rhs)
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

		GetUI().GetCanvas()->RenderCanvas();
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
	// bitmapPos is passed in meters.
	bool IsDrawable(ALLEGRO_BITMAP* bitmap, b2Vec2 bitmapPos, b2Vec2 bitmapCPos = b2Vec2(0,0))
	{
		auto& cam = GetRenderMgr().GetCam();

		b2Vec2 camTopL = cam->GetTopLeftPix();
		// Copy the vector then add it's with and height to get its bottom right
		b2Vec2 camBotR(camTopL);
		camBotR.x += cam->GetWidthPix();
		camBotR.y += cam->GetHeightPix();

		// Convert to pix
		bitmapPos = Utility::mtrToPix(bitmapPos);
		bitmapPos -= bitmapCPos;
		float bitmapWidth(al_get_bitmap_width(bitmap));
		float bitmapHeight(al_get_bitmap_height(bitmap));

		if (													// If none of the below statements are true then the bitmap is within view of the camera.
			(bitmapPos.x > (camBotR.x - 1))		||	// Is the left side of the bitmap to the right of the camera?
			((bitmapPos.x + bitmapWidth - 1) < camTopL.x)	||	// Is the right side of the bitmap to the left side of the camera?
			(bitmapPos.y > (camBotR.y - 1))		||	// Is the top of the bitmap below the camera?
			(bitmapPos.y + bitmapHeight - 1) < camTopL.y)		// Is the bottom of the bitmap above the camera?
			return false;

		return true;
	}

	bool Draw(ALLEGRO_BITMAP* bitmap, b2Vec2 dpos, int flags)
	{
		if (!bitmap)
			return false;
		if (!IsDrawable(bitmap, dpos))// Is the position to be drawn at out of view of the camera?
			return false;												// If so, don't waste CPU time drawing it.
		
		dpos = Utility::mtrToPix(dpos);		// Meters->Pixels
		
		b2Vec2 drawPos(Utility::GameToScreenPosPix(dpos));
		auto test = Utility::GameToScreenPosPix(dpos);
		al_draw_bitmap(bitmap, drawPos.x, drawPos.y, flags);

		return true;
	}
};