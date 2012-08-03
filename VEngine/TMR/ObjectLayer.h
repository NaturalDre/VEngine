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
		const Object* FindObject(const std::string& name) const;
		std::list<const Object*> FindObjects(const std::string& name) const;
		const std::list<Object>& GetObjects(void) { return m_objects; }
	private:
		std::list<Object> m_objects;
	};
};

#endif