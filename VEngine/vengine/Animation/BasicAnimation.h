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

	public:
		CBasicAnimation(const std::string& filename, size_t rows, size_t cols, double fps);
		~CBasicAnimation();

		ALLEGRO_BITMAP* GetFrame(void);
		void SetAlpha(size_t r, size_t g, size_t b);

	protected:
		ALLEGRO_BITMAP* m_animationSheet;
		ALLEGRO_BITMAP* m_frame;
		size_t m_frameW;
		size_t m_frameH;
	};
}
#endif