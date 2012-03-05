#include "vengine\Animation\AnimationBase.h"
#include <allegro5\allegro5.h>
#include <vengine\ObjectManager.h>
#include <vengine\Application.h>

namespace VE
{
	IAnimationBase::IAnimationBase(void)
		: m_holdAnimation(false)
		, m_timeout(1.0f)
		, m_fps(1.0f)
		, m_currentFrame(1)
		, m_rows(1)
		, m_cols(1)
	{
		GetObjMgr().Add(this);
	}

	IAnimationBase::~IAnimationBase(void)
	{
		GetObjMgr().Remove(this);
	}

	IAnimationBase::IAnimationBase(size_t rows, size_t cols, double fps)
		: m_rows(rows)
		, m_cols(cols)
		, m_fps(fps)
	{
		m_timeout = fps;
	}

	void IAnimationBase::NextFrame(void)
	{
		++m_currentFrame;
		// Are we at the end of the animation?
		if (m_currentFrame > (m_rows * m_cols))
			m_currentFrame = 1;	// If so, start over
	}

	void IAnimationBase::Logic(void)
	{
		m_timeout -= GetApp()->DeltaTime();
		if (m_timeout <= 0)
		{
			m_timeout = m_fps;
			NextFrame();
		}
	}

	void IAnimationBase::Reset(void)
	{
		m_currentFrame = 1;
		m_timeout = m_fps;
		m_holdAnimation = false;
	}
}