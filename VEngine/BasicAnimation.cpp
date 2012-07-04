#include "BasicAnimation.h"
#include <allegro5\allegro5.h>
#include "Utility.h"

#define DEFAULTFRAMEW 1
#define DEFAULTFRAMEH 1

namespace VE
{
	CBasicAnimation::CBasicAnimation(void)
		: IAnimationBase()
		, m_animationSheet()
		, m_frame()
		, m_frameW(DEFAULTFRAMEW)
		, m_frameH(DEFAULTFRAMEH)
	{

	}

	CBasicAnimation::CBasicAnimation(const std::string& filename, size_t rows, size_t cols, double fps)
		: IAnimationBase(rows, cols, fps)
		, m_animationSheet()
		, m_frame()
		, m_frameW(DEFAULTFRAMEW)
		, m_frameH(DEFAULTFRAMEH)
	{
		m_animationSheet = CBitmap(al_load_bitmap(filename.c_str()));

		if (m_animationSheet)
		{
			m_frameW = m_animationSheet.GetWidth() / GetCols();
			m_frameH = m_animationSheet.GetHeight() / GetRows();
			// Create the bitmap for the initial frame
			FrameChanged();
		}
	}

	CBasicAnimation::CBasicAnimation(ALLEGRO_BITMAP* sheet, size_t rows, size_t cols, double fps)
		: IAnimationBase(rows, cols, fps)
		, m_animationSheet(sheet)
		, m_frame()
		, m_frameW(DEFAULTFRAMEW)
		, m_frameH(DEFAULTFRAMEH)
	{
		assert(m_animationSheet.IsValid() == true);
		assert(rows > 0);
		assert(cols > 0);
		assert(fps > 0.0);

		if (!m_animationSheet || !GetRows() || !GetCols() || (GetFPS() <= 0))
			abort();

		if (m_animationSheet)
		{
			m_frameW = m_animationSheet.GetWidth() / GetCols();
			m_frameH = m_animationSheet.GetHeight() / GetRows();
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
			m_frame.Reset();
			//al_destroy_bitmap(m_frame);
			//m_frame = nullptr;
		}
	
		if (m_animationSheet)
		{
			m_animationSheet.Reset();
			//al_destroy_bitmap(m_animationSheet);
			//m_animationSheet = nullptr;
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
			m_frame.Reset();
			//al_destroy_bitmap(m_frame);
			//m_frame = nullptr;
		}
		m_frame = rhs.m_frame;
		rhs.Reset();
		//rhs.m_frame = nullptr;

		if (m_animationSheet)
		{
			m_animationSheet.Reset();
			//al_destroy_bitmap(m_animationSheet);
			//m_animationSheet = nullptr;
		}
		m_animationSheet = std::move(rhs.m_animationSheet);
		rhs.m_animationSheet.Reset();
		//rhs.m_animationSheet = nullptr;

		m_frameW = rhs.m_frameW;
		m_frameH = rhs.m_frameH;

		return *this;
	}

	CBasicAnimation::~CBasicAnimation()
	{
		if (m_frame)
		{
			m_frame.Reset();
			//al_destroy_bitmap(m_frame);
			//m_frame = nullptr;
		}

		if (m_animationSheet)
		{
			m_animationSheet.Reset();
			//al_destroy_bitmap(m_animationSheet);
			//m_animationSheet = nullptr;
		}
	}

	const CBitmap& CBasicAnimation::GetFrame(void)
	{
		return m_frame;
	}

	void CBasicAnimation::FrameChanged(void)
	{
		if (!m_animationSheet)
			return;

		ColRow cr = GetColRow(GetCols(), GetCurrentFrame());
		size_t x((cr.col - 1) * m_frameW);
		size_t y((cr.row - 1) * m_frameH);

		if (m_frame)
		{
			m_frame.Reset();
			//al_destroy_bitmap(m_frame);
			//m_frame = nullptr;
		}

		m_frame = CBitmap(m_animationSheet, x, y, m_frameW, m_frameH);
		//m_frame = al_create_sub_bitmap(m_animationSheet, x, y, m_frameW, m_frameH);
	}

	void CBasicAnimation::SetAlpha(size_t r, size_t g, size_t b)
	{
		m_animationSheet.ConvertMaskToAlpha(r, g, b);
		//al_convert_mask_to_alpha(m_animationSheet, al_map_rgb(r,g,b));
	}
}