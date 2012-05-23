#ifndef BOXVIEW_H
#define BOXVIEW_H

#include "ObjectView.h"

class BoxView: public VE::IObjectView
{
public:
	BoxView(void);
	void Draw(void);
};
#endif