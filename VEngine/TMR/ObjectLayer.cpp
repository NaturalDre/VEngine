#include "ObjectLayer.h"
#include "TiledLua.h"
#include <lua.hpp>
#include <assert.h>
#include <algorithm>
#include <luabind\luabind.hpp>

using namespace Tiled;

CObjectLayer::CObjectLayer(const luabind::object& objectlayer)
{
	if (!objectlayer.is_valid() || luabind::type(objectlayer) != LUA_TTABLE)
		return;

	SetName(luabind::object_cast<std::string>(objectlayer["name"]));
	// For some stupid reason the following 2 lines are not equivilent to
	// this one line: objectlayer["properties"].push(objectlayer.interpreter())
	// and ends up with ReadProperties not getting a table at the top of the stack.
	const luabind::object properties(objectlayer["properties"]);
	// STK: --
	properties.push(objectlayer.interpreter());
	// STK: -- table
	ReadProperties(objectlayer.interpreter(), this);
	lua_pop(objectlayer.interpreter(), 1);
	// STK: --
	for (luabind::iterator iter = luabind::iterator(objectlayer["objects"]), end; iter != end; ++iter)
		m_objects.push_back(Tiled::Object(*iter));
}

const Object* CObjectLayer::FindObject(const std::string& name) const
{
	for(auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if (iter->Name() == name)
			return &(*iter);
	}
	return nullptr;
}

std::list<const Object*> CObjectLayer::FindObjects(const std::string& name) const
{
	std::list<const Object*> objects;
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if (iter->Name() == name)
			objects.push_back(&(*iter));
	}
	return std::move(objects);
}