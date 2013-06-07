#include "Entity.h"
#include "Script.h"
#include "GameLevel.h"
#include "Component.h"
#include <luabind\luabind.hpp>
#include <luabind\adopt_policy.hpp>
namespace VE
{
	size_t IEntity::m_count = 0;

	IEntity::IEntity(CGameLevel* level)
		: m_gameLevel(level) 
		, m_enabled(true)
		//, m_script(nullptr)
		, m_entityID(++m_count)
	{
		if (m_gameLevel)
			m_gameLevel->AddEntity(this);
	}

	IEntity::~IEntity(void)
	{
		if (m_gameLevel)
			m_gameLevel->RemoveEntity(this);
	}

	void IEntity::Update(double dt)
	{
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
			(*iter)->Update(dt);
	}

	// Declared in source file because this is only for Lua
	class CEntityWrapper: public IEntity, public luabind::wrap_base
	{
	public: 
		CEntityWrapper(CGameLevel* gameLevel): IEntity(gameLevel) { }
		~CEntityWrapper(void) { }

		void Update(double dt) { IEntity::Update(dt); }
		static void DefaultUpdate(IEntity* ent, double dt) { return ent->IEntity::Update(dt); }
	};

	void IEntity::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<IEntity, CEntityWrapper>("IEntity")
				.def(constructor<CGameLevel*>())
				.property("groupName", &IEntity::GetGroupName)
				.property("entityID", &IEntity::GetEntityID)
				.property("position", &IEntity::GetPosition)
				.def("Update", &IEntity::Update, &CEntityWrapper::DefaultUpdate)
				.def("DefaultUpdate", &IEntity::Update)
				.def("Add", &IEntity::Add)
				.def("Remove", &IEntity::Remove)
			];
	}
}