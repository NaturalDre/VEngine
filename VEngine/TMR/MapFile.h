#ifndef MAPFILE_H
#define MAPFILE_H

#include <map>
#include <vector>
#include <string>
#include <luabind\object.hpp>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "Tileset.h"

struct lua_State;

namespace VE
{
	class CRender;
}

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

		MapProperties& Properties(void) { return m_properties; }
		std::vector<CTileLayer*>& TileLayers(void) { return m_tileLayers; }
		std::vector<CObjectLayer*>& ObjectLayers(void) { return m_objectLayers; }
		std::vector<CTileset*>& Tilesets(void) { return m_tilesets; }

		/*void RenderLayer(VE::CRender* renderer, CTileLayer* tilelayer);*/
	public:
		CMapFile(void);
		virtual ~CMapFile(void);

		bool Read(const std::string& mapFile);
		bool Read(const luabind::object& data);

		inline std::string GetVersion(void) const { return m_version; }
		inline std::string GetOrientation(void) const { return m_orientation; }
		inline const MapProperties Properties(void) const { return m_properties; }
		inline size_t GetWidth(void) const { return m_width; }
		inline size_t GetHeight(void) const { return m_height; }
		inline size_t GetTileWidth(void) const { return m_tileWidth; }
		inline size_t GetTileHeight(void) const { return m_tileHeight; }
		//inline size_t GetPlayerLayer(void) const { return m_playerLayer; }
		inline const std::vector<CTileLayer*>& GetTileLayers(void) const { return m_tileLayers; }
		inline const std::vector<CObjectLayer*>& GetObjectLayers(void) const { return m_objectLayers; }
		inline const std::vector<CTileset*>& GetTilesets(void) const { return m_tilesets; }
		//inline CObjectLayer* GetPhysicsLayer(void) const { return m_physicsLayer; }

		//inline void SetPlayerPlayer(size_t layer) { m_playerLayer = layer; }

		inline bool IsValid(void) const { return m_valid; }
		void Reset(void);

		//void Render(VE::CRender* renderer, size_t begin, size_t end);
	private:
		std::string m_version;
		std::string m_orientation;
		MapProperties m_properties;
		size_t m_width;
		size_t m_height;
		size_t m_tileWidth;
		size_t m_tileHeight;
		//size_t m_playerLayer;

		std::vector<CTileLayer*> m_tileLayers;
		std::vector<CObjectLayer*> m_objectLayers;
		std::vector<CTileset*> m_tilesets;
		//CObjectLayer* m_physicsLayer;
		bool m_valid;
	};
}
#endif