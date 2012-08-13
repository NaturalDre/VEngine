#ifndef RENDER_H
#define RENDER_H

#include "Camera.h"
#include "Process.h"
#include <vector>
#include <Gwen\Controls\Canvas.h>

namespace VE
{
	class IView;
	class CCamera;
	class CPhysics;
	class CBitmap;
	class CGameMap;

	class CRender: public IProcess
	{
	protected:
		void Think(double dt) { }

	public:
		CRender(void);
		~CRender(void);

		void AddView(IView* view);
		void RemoveView(IView* view);

		CGameMap* MapFile(void) const { return m_gameMap; }
		void SetMapFile(CGameMap* gameMap) { m_gameMap = gameMap; }

		CCamera* Cam(void) const { return m_camera; }
		//void SetCam(CCamera* cam) { m_camera = cam; }

		void SetPhysics(CPhysics* physics) { m_physics = physics; }
		void SetUICanvas(GwenCanvas* canvas) { m_uiCanvas = canvas; }
		void Render(void);
	private:
		std::vector<IView*> m_views;
		CGameMap* m_gameMap;
		CCamera* m_camera;
		// I only have a reference to the physics engine to draw the debug data for it.
		CPhysics* m_physics;
		GwenCanvas* m_uiCanvas;
	};
	// Current width of the screen window.
	size_t GetDisplayWidth(void);
	// Current height of the screen window.
	size_t GetDisplayHeight(void);
}
#endif