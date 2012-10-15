#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include "Entity.h"
#include "ContactCallback.h"

namespace VE
{
	class IPhysicsEntity: protected IContactCallback, public IEntity
	{
	protected:
		explicit IPhysicsEntity(CGameLevel* gameLevel): IEntity(gameLevel) { }

		/// @see ContactCallback.h
		virtual void BeginContact(b2Contact* contact) = 0;
		/// @see ContactCallback.h
		virtual void EndContact(b2Contact* contact) = 0;
		/// @see ContactCallback.h
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) { };
		/// @see ContactCallback.h
		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) { };

	public:
		static void Export(lua_State* L);
	};
}
#endif