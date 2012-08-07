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
		/// @see ContactCallback.h
		virtual void BeginContact(b2Contact* contact);
		/// @see ContactCallback.h
		virtual void EndContact(b2Contact* contact);

		static b2Body* CreateBody(CCube& cube, const b2Vec2& spawnPos);
		void Update(double dt);


	public:
		CCube(CGameLevel* gameLevel, const b2Vec2& spawnPos);
		~CCube(void);

		b2Body* GetBody(void) const { return m_body; }
	private:
		CCubeView* m_view;
		b2Body* m_body;
	};
}
#endif