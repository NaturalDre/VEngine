#ifndef POLY_H
#define POLY_H

#include "ObjectModel.h"
class b2Body;
class CPoly: public VE::IObjectModel
{
public:
	CPoly(void);
	~CPoly(void);
private:
	b2Body* m_body;
};
#endif