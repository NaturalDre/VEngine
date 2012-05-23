#ifndef RENDER_H
#define RENDER_H

#include <set>
#include "ObjectView.h"
#include "Camera.h"

namespace VE {
	class CApplicationImpl;
	class CRender
	{
		friend CApplicationImpl;
		friend IObjectView;
		friend CRender* Renderer(void);
	protected:
		CRender(void);

		// Draw the game world.
		void DrawScene(void);
		/*
		 * Register()
		 *
		 * Let CRender know this view exists so it can ask it to draw at render time.
		 *
		 * Params:
		 *	IObjectView* - View that needs to know when to draw.
		 *
		 * Notes:
		 *	Called by IObjectView's constructor
		 */
		void Register(IObjectView* view) { if (view) m_views.insert(view); }
		/*
		 * Deregister()
		 *
		 * Let CRender know this view no longer wants to be told when to draw.
		 *
		 * Params:
		 *	IObjectView* - View that no longer needs watching.
		 *
		 * Notes:
		 *	Called by IOjbectView's destructor
		 */
		void Deregister(IObjectView* view) { m_views.erase(view); }

	private:
		/*
		 * Destroy()
		 * 
		 * Free the global instance of CRender.
		 *
		 * Notes:
		 *	Called by CApplicationImpl on shutdown.
		 */
		static void Destroy(void);

	public:
		/* 
		 * SetPlayerLayer()
		 *
		 * Set what layer the player is currently on.
		 *
		 * Params:
		 *	int layer - The layer
		 *
		 * Notes:
		 *	CRender will draw all map layers below this layer, then
		 *	it will draw all game objects(which includes the player),
		 *  and finally draw the rest of the layers.
		 */
		inline void SetPlayerLayer(int layer) { m_playerLayer = layer; }
		// Returns a pointer to the camera the render is using to view the scene
		CCamera* Cam(void) const { return m_camera; }
	private:
		// Views that need to know when to draw.
		std::set<IObjectView*> m_views;
		// The layer that the player is on.
		int m_playerLayer;
		// The camera viewing the game world.
		CCamera* m_camera;
	};
	// Returns pointer to global instance of CRender
	CRender* Renderer(void);
}
#endif