#ifndef BOUNCER_H
#define BOUNCER_H

#include <vengine\GameObject.h>
#include <vengine\Tiled.h>
namespace VE
{
	class CBouncer: public NE::IGameObject
	{
	protected:
		void OnBeginContact(b2Contact* contact);
		void OnEndContact(b2Contact* contact);
		void OnPreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void OnPostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

		void OnUpdate(void);
	public:
		CBouncer(b2Vec2& pos, float widthMtrs, float heightMtrs);
		CBouncer(Tiled::TiledObject& data);
		~CBouncer(void);


		static int L_Create(lua_State* L);
	private:
		std::unique_ptr<b2Body, Utility::b2BodyDtor> m_body;
		double m_timeout;
	};
}
#endif