#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include <memory>

namespace VE
{
	class CCamera
	{
	protected:
		
	public:
		CCamera(std::weak_ptr<NE::IGameObject> obj, size_t widthPix, size_t heightPix);
		inline void SetTarget(NE::IGameObject* gameObj) { m_target = gameObj; }
		b2Vec2 GetPos(void) const;
		b2Vec2 GetTopLeftPix(void) const;
		b2Vec2 GetTopLeftMtrs(void) const;
		inline size_t GetWidthPix(void) const { return m_width; }
		inline size_t GetHeightPix(void) const { return m_height; }
	private:
		// Must exist.
		NE::IGameObject* m_target;
		size_t m_width;
		size_t m_height;
		
	};
}
#endif