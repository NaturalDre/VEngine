#ifndef BASICANIMATION_H
#define BASICANIMATION_H

#include <vengine\Animation\AnimationBase.h>

namespace VE
{
	class CBasicAnimation: public IAnimationBase
	{
	protected:

	public:
		CBasicAnimation(size_t rows, size_t cols, double fps);
		~CBasicAnimation();

	protected:
	};
}
#endif