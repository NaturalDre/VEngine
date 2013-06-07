#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <set>
#include <luabind\object.hpp>
#include <Box2D\Box2D.h>
class b2Contact;

namespace VE
{
	typedef std::set<const std::string> EntityGroups;

	//class CScript;
	class CGameLevel;
	class IComponent;
	class IEntity
	{
	protected:
		//void SetScript(CScript* script);

	public:
		IEntity(CGameLevel* level);

		virtual ~IEntity(void) = 0;
		virtual void Update(double dt);

		inline CGameLevel* GetGameLevel(void) const { return m_gameLevel; }

		virtual bool OnContact(IEntity* entity) { return false; } // Return true to accept he contact


		void AddEntityGroup(const std::string& group) { m_entityGroups.insert(group); }
		void RemoveEntityGroup(const std::string& group) { m_entityGroups.erase(group); }

		void Add(IComponent* c) { m_components.push_back(c); }
		void Remove(IComponent* c) { m_components.remove(c); }

		virtual b2Vec2 GetPosition(void) const { return b2Vec2(0, 0); }

		const std::string& GetGroupName(void) const { return m_groupName; }
		inline size_t GetEntityID(void) const { return m_entityID; }

		bool IsEnabled(void) const { return m_enabled; }
		void SetEnabled(bool enabled) { m_enabled = enabled; }

		//luabind::object operator[](const std::string& property);

		static void Export(lua_State* L);
	private:
		static size_t m_count;

		CGameLevel* m_gameLevel; // Game level this entity is a part of.
		//CScript* m_script;
		std::list<IComponent*> m_components;
		std::string m_groupName;
		const size_t m_entityID;
		bool m_enabled;
		EntityGroups m_entityGroups;
	};
}
#endif