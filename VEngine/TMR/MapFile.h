#ifndef MAPFILE_H
#define MAPFILE_H

#include <map>
#include <list>
#include <string>
#include <luabind\object.hpp>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "Tileset.h"

struct lua_State;

namespace Tiled
{
	class CTileLayer;
	class CObjectLayer;


	class CMapFile
	{
	protected:
		typedef std::map<const std::string, const std::string> MapProperties;
		static void LoadMapData(CMapFile& map, lua_State* L);
		static void LoadLayers(CMapFile& map, lua_State* L);

	public:
		CMapFile(void);
		~CMapFile(void);

		bool Read(const std::string& mapFile, std::string& err = std::string(""));
		bool Read(const luabind::object& data);

		inline std::string Version(void) const { return m_version; }
		inline std::string Orientation(void) const { return m_orientation; }
		inline const MapProperties Properties(void) const { return m_properties; }
		inline size_t Width(void) const { return m_width; }
		inline size_t Height(void) const { return m_height; }
		inline size_t TileWidth(void) const { return m_tileWidth; }
		inline size_t TileHeight(void) const { return m_tileHeight; }

		inline const std::list<CTileLayer*>& TileLayers(void) const { return m_tileLayers; }
		inline const std::list<CObjectLayer*>& ObjectLayers(void) const { return m_objectLayers; }
		inline const std::list<CTileset*>& Tilesets(void) const { return m_tilesets; }
		inline CObjectLayer* PhysicsLayer(void) const { return m_physicsLayer; }

		inline bool IsValid(void) const { return m_valid; }
		void Reset(void);

	private:
		std::string m_version;
		std::string m_orientation;
		std::map<const std::string, const std::string> m_properties;
		size_t m_width;
		size_t m_height;
		size_t m_tileWidth;
		size_t m_tileHeight;

		std::list<CTileLayer*> m_tileLayers;
		std::list<CObjectLayer*> m_objectLayers;
		std::list<CTileset*> m_tilesets;
		CObjectLayer* m_physicsLayer;
		bool m_valid;
	};
}
#endif