#ifndef VENGINE_H
#define VENGINE_H

#include <physfs.h>
#include "Utility.h"

#define VENGINE_BEGIN_NAMESPACE namespace VE {
#define VENGINE_END_NAMESPACE }
#define VENGINE_NAMESPACE VE

enum InitError 
{
	e_NoError,
	e_Core,
	e_Keyboard,
	e_Mouse,
	e_Image,
	e_Primitives,
	e_TTF
};

#endif