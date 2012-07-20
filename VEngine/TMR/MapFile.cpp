#include "MapFile.h"
#include <assert.h>
#include "Tilelayer.h"
#include "ObjectLayer.h"
#include "TiledLua.h"
#include <luabind\luabind.hpp>
#include "..\Utility.h"
#include <boost\foreach.hpp>

using namespace Tiled;

bool LoadTiledLib(lua_State* L)
{
	return !luaL_dofile(L, "Scripts/map/TiledLib.lua");
}

CMapFile::CMapFile(void)
{
	m_width = 0;
	m_height = 0;
	m_tileHeight = 0;
	m_tileWidth = 0;

	m_physicsLayer = nullptr;
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
		{

		}
		else if (type == "objectgroup")
		{

		}

		//const std::string type = luabind::call_function<std::string>(L, "GetLayerType", i);

		//if(type == "tilelayer")
		//{
		//	CTileLayer* layer = new CTileLayer;
		//	layer->ReadMap(L, i, &map);
		//	map.m_tileLayers.push_back(layer);
		//}
		//else if (type == "objectgroup")
		//{
		//	CObjectLayer* layer = new CObjectLayer;
		//	layer->ReadMapFile(&map, L, i);

		//	if (layer->Property("type") == "physics")
		//		map.m_physicsLayer = layer;
		//	else
		//		map.m_objectLayers.push_back(layer);
		//}
	}
}

bool CMapFile::Read(const std::string& mapFile, std::string& err)
{
	// Open an lua state
	lua_State* L = lua_open();
	luaL_openlibs(L);
	luabind::open(L);

	if (!L)
	{
		err = "Unable to create Lua State.";
		return false;
	}

	// Attempt to load the file.
	// NOTE: Non-zero is error.
	if (luaL_dofile(L, mapFile.c_str()))
	{
		err = "Unable to load file.";
		return false;
	}
	// Load the script which contains Lua functions for operating 
	// on Tiled's Lua map files.
	// NOTE: Non-zero is error
	if (!LoadTiledLib(L))
	{
		err = "Unable to load Lua file that contains functions for "
			"operating on Tiled's Lua map file.";
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
	
	delete m_physicsLayer;
	m_physicsLayer = nullptr;

	m_valid = false;
}