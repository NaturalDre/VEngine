#ifndef CUBEVIEW_H
#define CUBEVIEW_H

#include "View.h"
#include "Bitmap.h"

namespace VE
{
	class CCube;
	class CCubeView: public IView
	{
	protected:
		void Draw(void);

	public:
		CCubeView(CCube* cube, CRender* renderer);
		~CCubeView(void);

	private:
		CBitmap m_image;
		CCube* m_cube;
	};
}
#endif