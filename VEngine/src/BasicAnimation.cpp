#include "vengine\Animation\BasicAnimation.h"
#include <allegro5\allegro5.h>
#include <vengine\Utility.h>

#define DEFAULTFRAMEW 1
#define DEFAULTFRAMEH 1

namespace VE
{
	CBasicAnimation::CBasicAnimation(void)
		: IAnimationBase()
		, m_animationSheet(nullptr)
		, m_frame(nullptr)
		, m_frameW(DEFAULTFRAMEW)
		, m_frameH(DEFAULTFRAMEH)
	{

	}

	CBasicAnimation::CBasicAnimation(const std::string& filename, size_t rows, size_t cols, double fps)
		: IAnimationBase(rows, cols, fps)
		, m_animationSheet(nullptr)
		, m_frame(nullptr)
		, m_frameW(DEFAULTFRAMEW)
		, m_frameH(DEFAULTFRAMEH)
	{
		m_animationSheet = al_load_bitmap(filename.c_str());

		if (m_animationSheet)
		{
			m_frameW = al_get_bitmap_width(m_animationSheet) / GetCols();
			m_frameH = al_get_bitmap_height(m_animationSheet) / GetRows();
			// Create the bitmap for the initial frame
			FrameChanged();
		}
	}

	CBasicAnimation::CBasicAnimation(ALLEGRO_BITMAP* sheet, size_t rows, size_t cols, double fps)
		: IAnimationBase(rows, cols, fps)
		, m_animationSheet(sheet)
		, m_frame(nullptr)
		, m_frameW(DEFAULTFRAMEW)
		, m_frameH(DEFAULTFRAMEH)
	{
		assert(m_animationSheet != nullptr);
		assert(rows > 0);
		assert(cols > 0);
		assert(fps > 0.0);

		if (!m_animationSheet || !GetRows() || !GetCols() || (GetFPS() <= 0))
			abort();

		if (m_animationSheet)
		{
			m_frameW = al_get_bitmap_width(m_animationSheet) / GetCols();
			m_frameH = al_get_bitmap_height(m_animationSheet) / GetRows();
			FrameChanged();
		}
	}

	CBasicAnimation::CBasicAnimation(const CBasicAnimation& rhs)
		: IAnimationBase(rhs)
		, m_frame(nullptr)
		, m_animationSheet(nullptr)
		, m_frameW(0)
		, m_frameH(0)
	{
		*this = rhs;
	}

	CBasicAnimation::CBasicAnimation(CBasicAnimation&& rhs)
		: IAnimationBase(rhs)
		, m_frame(nullptr)
		, m_animationSheet(nullptr)
		, m_frameW(1)
		, m_frameH(1)
	{
		*this = std::move(rhs);
	}

	CBasicAnimation& CBasicAnimation::operator=(const CBasicAnimation& rhs)
	{
		if (this == &rhs)
			return *this;

		IAnimationBase::operator=(rhs);

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
		m_animationSheet = rhs.m_animationSheet;

		m_frameW = rhs.m_frameW;
		m_frameH = rhs.m_frameH;

		return *this;
	}

	CBasicAnimation& CBasicAnimation::operator=(CBasicAnimation&& rhs)
	{
		if (this == &rhs)
			return *this;

		IAnimationBase::operator=(std::move(rhs));

		if (m_frame)
		{
			al_destroy_bitmap(m_frame);
			m_frame = nullptr;
		}
		m_frame = rhs.m_frame;
		rhs.m_frame = nullptr;

		if (m_animationSheet)
		{
			al_destroy_bitmap(m_animationSheet);
			m_animationSheet = nullptr;
		}
		m_animationSheet = rhs.m_animationSheet;
		rhs.m_animationSheet = nullptr;

		m_frameW = rhs.m_frameW;
		m_frameH = rhs.m_frameH;

		return *this;
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
		return m_frame;
	}

	void CBasicAnimation::FrameChanged(void)
	{
		if (!m_animationSheet)
			return;

		b2Vec2 cr = Utility::GetColRow(GetCols(), GetCurrentFrame());
		size_t x((cr.x - 1) * m_frameW);
		size_t y((cr.y - 1) * m_frameH);

		if (m_frame)
		{
			al_destroy_bitmap(m_frame);
			m_frame = nullptr;
		}

		m_frame = al_create_sub_bitmap(m_animationSheet, x, y, m_frameW, m_frameH);
	}

	void CBasicAnimation::SetAlpha(size_t r, size_t g, size_t b)
	{
		al_convert_mask_to_alpha(m_animationSheet, al_map_rgb(r,g,b));
	}
}