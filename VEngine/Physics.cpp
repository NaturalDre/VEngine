#include "Physics.h"

namespace VE
{
	b2Vec2 GameToScreenPosPix(const b2Vec2& posPix)
	{ 
		//return posPix - VE::Renderer()->Cam()->TopLeftPosPix();
		return posPix - b2Vec2(0,0);
	}
}