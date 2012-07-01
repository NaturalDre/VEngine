#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include "Camera.h"

namespace Tiled
{
	class CMapFile;
}

namespace VE
{
	class IView;
	class CCamera;
	class CPhysics;
	class CBitmap;
	class CRender
	{
	public:
		CRender(void);
		~CRender(void);

		void AddView(IView* view);
		void RemoveView(IView* view);

		Tiled::CMapFile* MapFile(void) const { return m_mapFile; }
		void SetMapFile(Tiled::CMapFile* mapFile) { m_mapFile = mapFile; }

		CCamera* Cam(void) const { return m_camera; }
		void SetCam(CCamera* cam) { m_camera = cam; }

		void SetPhysics(CPhysics* physics) { m_physics = physics; }

		void Render(void);
	private:
		std::vector<IView*> m_views;
		Tiled::CMapFile* m_mapFile;
		CCamera* m_camera;
		// I only have a reference to the physics engine to draw the debug data for it.
		CPhysics* m_physics;
	};

	// Current width of the screen window.
	size_t GetDisplayWidth(void);
	// Current height of the screen window.
	size_t GetDisplayHeight(void);
}
#endif