#ifndef BARREL_H
#define BARREL_H

#include "Entity.h"

class b2Body;

namespace VE
{
	class CBarrel: public IEntity
	{
	protected:
		bool OnContact(IProjectile* bullet);
		void Update(double dt);
	public:
		CBarrel(CGameLevel* level);
		~CBarrel(void);

	private:
		float m_health;
		b2Body* m_body;
	};
};
#endif