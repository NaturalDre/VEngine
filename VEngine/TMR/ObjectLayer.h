#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Layer.h"
#include "Object.h"
#include <list>
#include <luabind\object.hpp>

struct lua_State;

namespace Tiled
{
	class CMapFile;

	class CObjectLayer: public ILayer
	{
	public:
		CObjectLayer(const luabind::object& objectlayer);

		int GetType(void) const { return e_ObjectLayer; }

		const std::list<Object>& Objects(void) { return m_objects; }

		std::string Property(const std::string& prop);
	private:
		std::list<Object> m_objects;
	};
};

#endif