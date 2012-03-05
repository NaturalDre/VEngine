#include "vengine\Camera.h"
#include "vengine\Physics.h"

namespace VE
{
	CCamera::CCamera(std::weak_ptr<NE::IGameObject> obj, size_t widthPix, size_t heightPix)
		: m_target(nullptr)
		, m_width(widthPix)
		, m_height(heightPix)
	{
		
	}

	b2Vec2 CCamera::GetPos(void) const
	{
		if (m_target)
			return m_target->GetPos();
		return b2Vec2(0,0);
	}

	b2Vec2 CCamera::GetTopLeftPix(void) const 
	{
		b2Vec2 tl = Utility::mtrToPix(GetPos());

		tl.x -= m_width / 2.0f;
		tl.y -= m_height / 2.0f;

		return tl;
	}

	b2Vec2 CCamera::GetTopLeftMtrs(void) const
	{
		return Utility::pixToMtr(GetTopLeftPix());
	}
}