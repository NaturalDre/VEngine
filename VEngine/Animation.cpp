#include "Animation.h"
#include "GameLevel.h"

namespace VE
{
	IAnimation::IAnimation(bool autoLogic)
	{
		if (autoLogic)
			GameLevel()->AddAnimation(this);
	}

	IAnimation::~IAnimation(void)
	{
		GameLevel()->RemoveAnimation(this);
	}
}