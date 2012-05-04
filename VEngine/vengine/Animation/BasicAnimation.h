#ifndef BASICANIMATION_H
#define BASICANIMATION_H

#include <vengine\Animation\AnimationBase.h>
#include <string>

struct ALLEGRO_BITMAP;

namespace VE
{
	class CBasicAnimation: public IAnimationBase
	{
	protected:
		inline void SetAnimationSheet(ALLEGRO_BITMAP* bitmap) { m_animationSheet = bitmap; }
		inline void SetFrame(ALLEGRO_BITMAP* bitmap) { m_frame = bitmap; };
		inline void SetFrameW(size_t frameW) { m_frameW = frameW; }
		inline void SetFrameH(size_t frameH) { m_frameH = frameH; }

		void FrameChanged(void);

	public:
		CBasicAnimation(void);
		CBasicAnimation(const std::string& filename, size_t rows, size_t cols, double fps);
		CBasicAnimation(ALLEGRO_BITMAP* sheet, size_t rows, size_t cols, double fps);
		CBasicAnimation(const CBasicAnimation& rhs);
		CBasicAnimation(CBasicAnimation&& rhs);

		~CBasicAnimation();

		CBasicAnimation& operator=(const CBasicAnimation& rhs);
		CBasicAnimation& operator=(CBasicAnimation&& rhs);

		ALLEGRO_BITMAP* GetFrame(void);
		void SetAlpha(size_t r, size_t g, size_t b);

		inline ALLEGRO_BITMAP* GetAnimationSheet(void) const { return m_animationSheet; }
		inline ALLEGRO_BITMAP* GetFrame(void) const { return m_frame; }

		inline size_t GetFrameW(void) const { return m_frameW; }
		inline size_t GetFrameH(void) const { return m_frameH; }

	private:
		ALLEGRO_BITMAP* m_animationSheet;
		ALLEGRO_BITMAP* m_frame;
		size_t m_frameW;
		size_t m_frameH;
	};
}
#endif