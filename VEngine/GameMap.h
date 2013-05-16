#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "TMR\MapFile.h"
#include "Bitmap.h"
#include "MapParser.h"
#include <map>
#include "Physics.h"

struct lua_State;

namespace VE
{
	class CRender;
	class CGameLevel;
	class CGameMap: public Tiled::CMapFile
	{
		friend CMapParser;
	public:
		typedef std::vector<Tiled::CTileLayer*>::const_iterator ConstTileLayerIter;

	protected:
		CBitmap LoadTile(const size_t id);
		ConstTileLayerIter FindTileLayer(const std::string& name);
		int FindTileLayerIndex(const std::string& name);

		void RenderLayer(VE::CRender* renderer, Tiled::CTileLayer* tilelayer);
		void RenderOrthogonal(VE::CRender* renderer, Tiled::CTileLayer* tilelayer);
		void RenderIsometric(VE::CRender* renderer, Tiled::CTileLayer* tilelayer);
		/// @param pos Position on the map to spawn the player in pixels.
		void SetPlayerSpawn(float x, float y) { m_playerSpawn = PixToMtr(b2Vec2(x,y)); }
		void SetPlayerSpawn(const b2Vec2& pos) { m_playerSpawn = pos; };
	public:

		CGameMap(CGameLevel* gameLevel);
		~CGameMap(void) { }

		bool Read(const std::string& filename);
		void Render(VE::CRender* renderer, size_t begin, size_t end);
		void Render(VE::CRender* renderer, const std::string& begin, const std::string& end);

		inline size_t GetPlayerLayer(void) const { return m_playerLayer; }
		/// @param name The name of the tileset you want.
		/// \return A pointer to the tileset. nullptr if none found.
		const CBitmap* GetTilesetImage(const std::string& name) const;
		/// \return Position in meters.
		b2Vec2 GetPlayerSpawn(void) const { return m_playerSpawn; }

		inline void SetPlayerLayer(const std::string& layerName) { m_playerLayer = FindTileLayerIndex(layerName); }
		inline void SetPlayerLayer(size_t layerIndex) { m_playerLayer = layerIndex; }

		static void Export(lua_State* L);
	private:
		std::map<std::string, CBitmap> m_tilesetImages;
		CMapParser m_parser;
		CGameLevel* m_gameLevel;

		size_t m_playerLayer;
		b2Vec2 m_playerSpawn;
		Tiled::Object m_playerData;
	};
}

#endif