#ifndef ENTITY_H
#define ENTITY_H

#include <list>

#ifndef CALLSCRIPTFUNCTION
#define CALLSCRIPTFUNCTION
#define CallFunction luabind::call_function<luabind::object>
#endif

class b2Contact;

namespace VE
{
	class CScript;
	class IProjectile;
	class CGameLevel;
	class IEntity
	{
	public:
		IEntity(CGameLevel* level);

		virtual ~IEntity(void);
		virtual void Update(double deltaTime);

		inline CGameLevel* GetGameLevel(void) const { return m_gameLevel; }

		virtual bool OnContact(IProjectile* projectile, b2Contact* contact = nullptr) { return false; } // Return true to accept the contact
		virtual bool OnContact(IEntity* entity) { return false; } // Return true to accept he contact

		CScript* GetScript(void) const { return m_script; }
	private:
		CGameLevel* m_gameLevel; // Game level this entity is a part of.
		CScript* m_script;
	};
}
#endif