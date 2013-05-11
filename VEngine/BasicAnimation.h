#ifndef BASICANIMATION_H
#define BASICANIMATION_H

#include "AnimationBase.h"
#include <string>
#include <allegro5\allegro5.h>
#include "Bitmap.h"
#include <memory>

namespace VE
{
	class CBasicAnimation: public IAnimationBase
	{
	protected:
		//inline void SetAnimationSheet(ALLEGRO_BITMAP* bitmap) { m_animationSheet = bitmap; }
		//inline void SetFrame(ALLEGRO_BITMAP* bitmap) { m_frame = bitmap; };
		inline void SetFrameW(size_t frameW) { m_frameW = frameW; }
		inline void SetFrameH(size_t frameH) { m_frameH = frameH; }

		void FrameChanged(void);

	public:
		CBasicAnimation(void);
		//CBasicAnimation(const std::string& filename, size_t rows, size_t cols, double fps);
		CBasicAnimation(const std::shared_ptr<CBitmap>& sheet, size_t rows, size_t cols, double fps);
		CBasicAnimation(const CBasicAnimation& rhs);
		CBasicAnimation(CBasicAnimation&& rhs);

		~CBasicAnimation();

		CBasicAnimation& operator=(const CBasicAnimation& rhs);
		CBasicAnimation& operator=(CBasicAnimation&& rhs);

		const CBitmap& GetFrame(void);
		void SetAlpha(size_t r, size_t g, size_t b);

		inline const std::shared_ptr<CBitmap>& GetAnimationSheet(void) const { return m_animationSheet; }
		inline const CBitmap& GetFrame(void) const { return m_frame; }

		inline size_t GetFrameW(void) const { return m_frameW; }
		inline size_t GetFrameH(void) const { return m_frameH; }

	private:
		std::shared_ptr<CBitmap> m_animationSheet; /// The spritesheet. Owned by AssetManager.
		CBitmap m_frame;
		size_t m_framePosX;
		size_t m_framePosY;
		size_t m_frameW;
		size_t m_frameH;
	};
}
#endif