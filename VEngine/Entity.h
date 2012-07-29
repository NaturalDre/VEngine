#ifndef ENTITY_H
#define ENTITY_H

#include <list>

namespace VE
{
	class CScript;
	class IBullet;
	class CGameLevel;
	class IEntity
	{
	public:
		IEntity(CGameLevel* level);

		virtual ~IEntity(void);
		virtual void Update(double deltaTime);

		inline CGameLevel* GameLevel(void) const { return m_gameLevel; }

		virtual bool OnContact(IBullet* bullet) { return false; } // Return true to accept he contact
		virtual bool OnContact(IEntity* entity) { return false; } // Return true to accept he contact

		void AddScript(CScript* script) { m_scripts.push_back(script); }
		void RemoveScript(CScript* script) { m_scripts.remove(script); }

		const std::list<CScript*>& GetScripts(void) const { return m_scripts; }
		std::list<CScript*>& GetScripts(void) { return m_scripts; }
	private:
		CGameLevel* m_gameLevel; // Game level this entity is a part of.
		std::list<CScript*> m_scripts;
	};
}
#endif