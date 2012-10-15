#ifndef CUBE_H
#define CUBE_H

#include "Enemy.h"
#include <Box2D\Dynamics\b2Body.h>
#include <luabind\object.hpp>
namespace VE
{
	class CCubeView;
	class CCube: public IEnemy
	{
	protected:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);

		bool OnContact(IProjectile* projectile);
		void OnDeath(void);
		void Update(double dt);


		static b2Body* CreateBody(CCube& cube, const b2Vec2& spawnPos);

	public:
		CCube(CGameLevel* gameLevel, const b2Vec2& spawnPos);
		~CCube(void);

		b2Body* GetBody(void) const { return m_body; }
		float GetHealth(void) const { return m_health; }
		bool GetDeleteOnDeath(void) { return m_deleteOnDeath; }
		void SetDeleteOnDeath(bool shouldDelete) { m_deleteOnDeath = shouldDelete; }
		static void Export(lua_State* L);
	private:
		CCubeView* m_view;
		b2Body* m_body;
		CScript* m_script;
		float m_health;
		bool m_deleteOnDeath;
	};
}
#endif