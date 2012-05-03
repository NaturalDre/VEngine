#include "vengine\Animation\BasicAnimation.h"
#include <allegro5\allegro5.h>
#include <vengine\Utility.h>

namespace VE
{
	CBasicAnimation::CBasicAnimation(const std::string& filename, size_t rows, size_t cols, double fps)
		: IAnimationBase(rows, cols, fps)
		, m_animationSheet(nullptr)
		, m_frameW(0)
		, m_frameH(0)
		, m_frame(nullptr)
	{
		m_animationSheet = al_load_bitmap(filename.c_str());

		if (m_animationSheet)
		{
			m_frameW = al_get_bitmap_width(m_animationSheet) / GetCols();
			m_frameH = al_get_bitmap_height(m_animationSheet) / GetRows();
		}
	}

	CBasicAnimation::~CBasicAnimation()
	{
		if (m_frame)
		{
			al_destroy_bitmap(m_frame);
			m_frame = nullptr;
		}

		if (m_animationSheet)
		{
			al_destroy_bitmap(m_animationSheet);
			m_animationSheet = nullptr;
		}
	}

	ALLEGRO_BITMAP* CBasicAnimation::GetFrame(void)
	{
		if (!m_animationSheet)
			return nullptr;

		b2Vec2 cr = Utility::GetColRow(GetCols(), GetCurrentFrame());
		size_t x((cr.x - 1) * m_frameW);
		size_t y((cr.y - 1) * m_frameH);

		if (m_frame)
		{
			al_destroy_bitmap(m_frame);
			m_frame = nullptr;
		}

		return m_frame = al_create_sub_bitmap(m_animationSheet, x, y, m_frameW, m_frameH);
	}

	void CBasicAnimation::SetAlpha(size_t r, size_t g, size_t b)
	{
		al_convert_mask_to_alpha(m_animationSheet, al_map_rgb(r,g,b));
	}
}