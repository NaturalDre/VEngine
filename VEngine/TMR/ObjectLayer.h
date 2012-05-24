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
		typedef std::map<const std::string, const std::string> LayerProperties;	
	public:
		CObjectLayer(void);

		void ReadMapFile(CMapFile* mapFile, lua_State* L, size_t layer);

		int Type(void) const { return e_ObjectLayer; }

		LayerProperties Properties(void) const { return m_properties; }
		const std::list<TiledObject>& Objects(void) { return m_objects; }


		std::string Property(const std::string& prop);
	private:
	
		LayerProperties m_properties;
		std::list<TiledObject> m_objects;
	};
};

#endif