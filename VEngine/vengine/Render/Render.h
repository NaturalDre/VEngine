#ifndef RENDER_H
#define RENDER_H

#include <allegro5\allegro5.h>
#include <memory>
#include <list>
#include "vengine\Image.h"
#include "vengine\Render\RenderListener.h"
#include "vengine\Camera.h"

#define BLACK al_map_rgb(0,0,0)
#define CLEARTOBLACK al_clear_to_color(BLACK)
// Forwards
namespace VE
{
	class CApplicationImpl;
	class IRenderListener;
}

namespace VE
{
	namespace Global
	{
		extern const float FPS;
	}

	namespace Utility
	{
		struct AlBitmapDel
		{
			void operator()(ALLEGRO_BITMAP* ptr) const { if (ptr) al_destroy_bitmap(ptr); ptr = nullptr; }
		};
		struct AlDisplayDel
		{
			void operator()(ALLEGRO_DISPLAY* ptr) const { if (ptr) al_destroy_display(ptr); ptr = nullptr; }
		};
	}
}

namespace VE
{
	class CRenderManager
	{
		friend CApplicationImpl;
		friend IRenderListener;
		friend CRenderManager& GetRenderMgr(void);
	protected:
		// Add a listener to the manager. (Called be IRenderListener's constructor)
		void AddListener(IRenderListener* listener) { m_listeners.push_back(listener); }
		// Remove a listener from the manager. (Called by IRenderListener's destructor)
		void RemoveListener(IRenderListener* listener) { m_listeners.remove(listener); }
		// Initialize the renderer and create the display
		int Init(size_t width, size_t height);
		// Does per frame computations
		void Logic(void);
		// Render everything to the screen
		void Render(void);
		// Frees/stores necessary data 
		void Cleanup(void);
	public:
		// Render manager will own the camera
		void SetCamera(CCamera* cam) { m_cam.reset(cam); }
		//
		const std::unique_ptr<CCamera>& GetCam(void) { return m_cam; }
	private:
		CRenderManager(void);
		void SortListeners(void);

		std::unique_ptr<ALLEGRO_DISPLAY, Utility::AlDisplayDel> m_display;
		std::unique_ptr<CCamera> m_cam;
		std::list<IRenderListener*> m_listeners;
		bool m_isInit;
	};

	CRenderManager& GetRenderMgr(void);

	inline float GetScreenW(void) { return al_get_display_width(al_get_current_display()); }
	inline float GetScreenH(void) { return al_get_display_height(al_get_current_display()); }

	bool Draw(ALLEGRO_BITMAP* bitmap, b2Vec2 dpos, int flags); 
}
#endif