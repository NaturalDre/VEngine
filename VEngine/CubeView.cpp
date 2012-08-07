#include "CubeView.h"
#include "Cube.h"
#include "Render.h"
#include <assert.h>

namespace VE
{
	CCubeView::CCubeView(CCube* cube, CRender* renderer)
		: IView(renderer)
		, m_cube(cube)
	{
		assert(m_cube != nullptr);
		m_image = CBitmap("Images/Enemies/cube1.png");
		assert(m_image.IsValid() == true);
	}

	CCubeView::~CCubeView(void)
	{
		m_cube = nullptr;
	}

	void CCubeView::Draw(void)
	{
		if (!m_cube || !m_image)
			return;

		DrawBitmap(m_image, m_cube->GetBody()->GetPosition(), b2Vec2(0.0f, 0.0f));
	}
}