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
	class CRender
	{
	public:
		CRender(void);
		~CRender(void);

		void AddView(IView* view);
		void RemoveView(IView* view);

		Tiled::CMapFile* MapFile(void) const { return m_mapFile; }

		void Render(void);
	private:
		std::vector<IView*> m_views;
		Tiled::CMapFile* m_mapFile;
	};
}
#endif