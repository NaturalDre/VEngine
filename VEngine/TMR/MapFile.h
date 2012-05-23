#ifndef MAPFILE_H
#define MAPFILE_H

#include <map>
#include <list>
#include <string>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "Tileset.h"

struct lua_State;

namespace Tiled
{
	class CTileLayer;
	class CObjectLayer;

	typedef std::map<const std::string, const std::string> Properties;
	class CMapFile
	{
		void LoadMapData(lua_State* L);
		void LoadLayers(lua_State* L);
	public:
		CMapFile(void);

		bool ReadMapFile(const std::string& mapFile, std::string& err = std::string(""));

		inline std::string GetVersion(void) const { return m_version; }
		inline std::string GetOrientation(void) const { return m_orientation; }
		inline const Properties GetProperties(void) const { return m_properties; }
		inline size_t GetWidth(void) const { return m_width; }
		inline size_t GetHeight(void) const { return m_height; }
		inline size_t GetTileWidth(void) const { return m_tileWidth; }
		inline size_t GetTileHeight(void) const { return m_tileHeight; }

		inline const std::list<CTileLayer*>& GetTileLayers(void) const { return m_tileLayers; }
		inline const std::list<CObjectLayer*>& GetObjectLayers(void) const { return m_objectLayers; }
		inline const std::list<CTileset*>& GetTilesets(void) const { return m_tilesets; }
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
		bool m_valid;
	};
}
#endif