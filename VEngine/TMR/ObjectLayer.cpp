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