#include "Entity.h"
#include "Script.h"
#include "GameLevel.h"
#include <luabind\luabind.hpp>

namespace VE
{
	size_t IEntity::m_count = 0;

	IEntity::IEntity(CGameLevel* level)
		: m_gameLevel(level) 
		, m_script(nullptr)
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

	void IEntity::SetScript(CScript* script)
	{
		delete m_script;
		m_script = script;
	}

	void IEntity::Update(double deltaTime)
	{
		m_script->Update(deltaTime);
	}

	luabind::object IEntity::operator[](const std::string& property)
	{
		if (!m_script || !m_script->IsValid())
			return luabind::object();
		
		auto obj = m_script->GetSelf();
		return obj[property];
	}

	void IEntity::Export(lua_State* L)
	{
		using namespace luabind;
		module(L)
			[
				class_<IEntity>("IEntity")
				.property("groupName", &IEntity::GetGroupName)
				.property("entityID", &IEntity::GetEntityID)
			];
	}
}