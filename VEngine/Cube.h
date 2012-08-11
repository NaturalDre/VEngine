#ifndef CUBE_H
#define CUBE_H

#include "Enemy.h"
#include <Box2D\Dynamics\b2Body.h>

namespace VE
{
	class CCubeView;
	class CCube: public IEnemy
	{
	protected:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);

		bool OnContact(IProjectile* projectile);
		static b2Body* CreateBody(CCube& cube, const b2Vec2& spawnPos);
		void Update(double dt);


	public:
		CCube(CGameLevel* gameLevel, const b2Vec2& spawnPos);
		~CCube(void);

		b2Body* GetBody(void) const { return m_body; }
	private:
		CCubeView* m_view;
		b2Body* m_body;

		float m_health;
	};
}
#endif