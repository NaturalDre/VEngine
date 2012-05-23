#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include <list>
#include "Layer.h"
#include "TiledObject.h"

struct lua_State;

namespace Tiled
{
	class CMapFile;
	class CObjectLayer: public ILayer
	{
	public:
		CObjectLayer(void);
		int Type(void) const { return e_ObjectLayer; }
		void ReadMapFile(CMapFile* mapFile, lua_State* L, size_t layer);

	private:
		std::map<const std::string, const std::string> m_properties;
		std::list<TiledObject> m_objects;
	};
};

#endif