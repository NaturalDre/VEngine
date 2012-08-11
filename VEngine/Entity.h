#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <set>
#include <luabind\object.hpp>

#ifndef CALLSCRIPTFUNCTION
#define CALLSCRIPTFUNCTION
#define L_CallFunction luabind::call_function<luabind::object>
#endif

class b2Contact;


namespace VE
{
	typedef std::set<const std::string> EntityGroups;

	class CScript;
	class IProjectile;
	class CGameLevel;
	class IEntity
	{
	protected:
		void SetScript(CScript* script);

	public:
		IEntity(CGameLevel* level);

		virtual ~IEntity(void);
		virtual void Update(double deltaTime);

		inline CGameLevel* GetGameLevel(void) const { return m_gameLevel; }

		virtual bool OnContact(IProjectile* projectile) { return false; } // Return true to accept the contact
		virtual bool OnContact(IEntity* entity) { return false; } // Return true to accept he contact

		CScript* GetScript(void) const { return m_script; }

		void AddEntityGroup(const std::string& group) { m_entityGroups.insert(group); }
		void RemoveEntityGroup(const std::string& group) { m_entityGroups.erase(group); }

		const std::string& GetGroupName(void) const { return m_groupName; }
		inline size_t GetEntityID(void) const { return m_entityID; }


		luabind::object operator[](const std::string& property);
	private:
		static size_t m_count;

		CGameLevel* m_gameLevel; // Game level this entity is a part of.
		CScript* m_script;

		std::string m_groupName;
		const size_t m_entityID;
		EntityGroups m_entityGroups;
	};
}
#endif