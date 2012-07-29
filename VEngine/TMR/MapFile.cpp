#include "MapFile.h"
#include <assert.h>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "TiledLua.h"
#include "..\Utility.h"
#include "..\Bitmap.h"
#include "..\Render.h"
#include <luabind\luabind.hpp>

#include <boost\foreach.hpp>

using namespace Tiled;

bool LoadTiledLib(lua_State* L)
{
	return DoFile(L, "Scripts/map/TiledLib.lua");
}

CMapFile::CMapFile(void)
{
	m_width = 0;
	m_height = 0;
	m_tileHeight = 0;
	m_tileWidth = 0;
	//m_playerLayer = 1;

	//m_physicsLayer = nullptr;
	m_valid = false;
}

CMapFile::~CMapFile(void)
{
	Reset();
}
void CMapFile::LoadMapData(CMapFile& map, lua_State* L)
{
	map.m_version = luabind::call_function<std::string>(L, "GetMapVersion");
	map.m_orientation = luabind::call_function<std::string>(L, "GetMapOrientation");
	map.m_width = luabind::call_function<size_t>(L, "GetMapWidth");
	map.m_height = luabind::call_function<size_t>(L, "GetMapHeight");
	map.m_tileWidth = luabind::call_function<size_t>(L, "GetMapTileWidth");
	map.m_tileHeight = luabind::call_function<size_t>(L, "GetMapTileHeight");
}

void CMapFile::LoadLayers(CMapFile& map, lua_State* L)
{

	for (size_t i = 1; i <= luabind::call_function<size_t>(L, "GetNumberOfTilesets"); ++i)
		map.m_tilesets.push_back(new CTileset(luabind::call_function<luabind::object>(L, "GetTileset", i)));


	for (size_t i = 1, max = luabind::call_function<size_t>(L, "GetNumberOfLayers"); i <= max; ++i)
	{
		luabind::object data = luabind::call_function<luabind::object>(L, "GetLayer", i);

		if (!data.is_valid())
			break;

		const std::string type = luabind::object_cast<std::string>(data["type"]);

		if (type == "tilelayer")
			map.m_tileLayers.push_back( new CTileLayer(data, map));
		else if (type == "objectgroup")
		{
			CObjectLayer* layer = new CObjectLayer(data);
			map.m_objectLayers.push_back(layer);
			//if (layer->GetProperty("type") == "physics")
			//	map.m_physicsLayer = layer;
			//else
			//	map.m_objectLayers.push_back(layer);
		}
	}
}

//void CMapFile::RenderLayer(VE::CRender* renderer, CTileLayer* tilelayer)
//{
//		// FOr the sub bitmaps
//		VE::CBitmap tile;
//		size_t prevID(0);
//
//		// Top left x and y position of the camera
//		const float tlx = renderer->Cam()->TopLeftPosPix().x;
//		const float tly = renderer->Cam()->TopLeftPosPix().y;	
//
//
//		const int startCol(static_cast<int>(tlx / GetTileWidth()));
//		const int startRow(static_cast<int>(tly / GetTileHeight()));
//
//
//		const int endCol = startCol + (VE::GetDisplayWidth() / GetTileWidth()) + 2; // +2 is buffer otherwise last col won't draw
//		const int endRow = startRow + (VE::GetDisplayHeight() / GetTileHeight()) + 2; // +2 is buffer otherwise last row won't draw
//
//		for (int row = startRow; row < endRow; ++row)
//		{
//			for (int col = startCol; col < endCol; ++col)
//			{
//				int id = tilelayer->GetDataVal(row, col);
//				if (id == 0)
//					continue;
//				if (id != prevID)
//				{
//					prevID = id;
//					tile = Tiled::CTileset::LoadTile(GetTilesets(), id);
//				}
//
//				prevID = id;
//
//				int dx = col * GetTileWidth();
//				int dy = row * GetTileHeight();
//
//				if (tile)
//					DrawBitmap(tile, VE::PixToMtr(b2Vec2(static_cast<float>(dx), static_cast<float>(dy))));
//			}
//		}
//}

bool CMapFile::Read(const std::string& mapFile)
{
	Reset();
	// Open an lua state
	lua_State* L = lua_open();
	if (!L)
		return false;

	luaL_openlibs(L);
	luabind::open(L);

	// Attempt to load the file and load the script which 
	// contains Lua functions for operating on Tiled's 
	// Lua map files.
	// NOTE: Non-zero is error.
	if (luaL_dofile(L, mapFile.c_str()) || !LoadTiledLib(L))
	{
		lua_close(L);
		return false;
	}

	LoadMapData(*this, L);
	LoadLayers(*this, L);

	lua_close(L);
	return m_valid = true;
}

bool CMapFile::Read(const luabind::object& data)
{
	if (!data.is_valid() || !LoadTiledLib(data.interpreter()))
		return false;

	LoadMapData(*this, data.interpreter());
	LoadLayers(*this, data.interpreter());

	return m_valid = true;
}

void CMapFile::Reset(void)
{
	m_version.clear();
	m_orientation.clear();
	m_properties.clear();
	m_width = 0;
	m_height = 0;
	m_tileWidth = 0;
	m_tileHeight = 0;

	BOOST_FOREACH(CTileLayer* tilelayer, m_tileLayers)
		delete tilelayer;
	m_tileLayers.clear();

	BOOST_FOREACH(CObjectLayer* objectlayer, m_objectLayers)
		delete objectlayer;
	m_objectLayers.clear();

	BOOST_FOREACH(CTileset* tileset, m_tilesets)
		delete tileset;
	m_tilesets.clear();
	
	//delete m_physicsLayer;
	//m_physicsLayer = nullptr;

	m_valid = false;
}

//void Tiled::CMapFile::Render(VE::CRender* renderer,  size_t begin, size_t end)
//{
//	for (size_t i = begin; (i < m_tileLayers.size()) && (i <= end); ++i)
//		RenderLayer(renderer, m_tileLayers.at(i));
//}