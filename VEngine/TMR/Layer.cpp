#include "Layer.h"
#include <lua.hpp>
#include <luabind\object.hpp>

namespace Tiled
{
	void ILayer::ReadProperties(lua_State* L, ILayer* layer)
	{
		const luabind::object table(luabind::from_stack(L, -1));
		if (luabind::type(table) != LUA_TTABLE)
			return;

		for (luabind::iterator iter = luabind::iterator(table), end; iter != end; ++iter)
		{
			layer->m_properties.insert(std::pair<const std::string, const std::string>
				(luabind::object_cast<const std::string>(iter.key())
				, luabind::object_cast<std::string>(*iter)));
		}
	}

	std::string ILayer::GetProperty(const std::string& prop)
	{
		auto iter = m_properties.find(prop);
		if (iter != m_properties.end())
			return iter->second;
		return "";
	}
}